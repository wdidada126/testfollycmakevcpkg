// TestFolly/AtomicIntrusiveHashMapTest.cpp
//
// 实测结论（2026-09-25）：folly::AtomicIntrusiveHashMap 这个容器在开源 folly 中【不存在】。
// 证据链见同目录 AtomicIntrusiveHashMap.md。直接写下面的 include 会得到：
//     fatal error C1083: 无法打开包括文件: folly/container/AtomicIntrusiveHashMap.h
// // #include <folly/container/AtomicIntrusiveHashMap.h>
//
// 本文件改为实测同名字族里【真实存在】的无锁侵入式容器：
//     folly/AtomicIntrusiveLinkedList.h
// 提供 AtomicIntrusiveLinkedListHook<T>（单指针 next 钩子）和
// AtomicIntrusiveLinkedList<T, &T::hook>（CAS 无锁头插链表）。
//
// 用法模板（头文件注释原版）：
//   class MyClass { AtomicIntrusiveLinkedListHook<MyClass> hook_; }
//   AtomicIntrusiveLinkedList<MyClass, &MyClass::hook_> list;
//   list.insert(&a);
//   list.sweep([](MyClass* c) { doSomething(c); });

#include <folly/AtomicIntrusiveLinkedList.h>

#include <atomic>
#include <cassert>
#include <cstdio>
#include <thread>
#include <vector>

using namespace folly;

// ---------- 侵入式元素：hook 内嵌在对象里，容器不分配内存 ----------
class Node {
 public:
  AtomicIntrusiveLinkedListHook<Node> hook;
  int id;
  int thread;

  Node(int i, int t = 0) : id(i), thread(t) {}
};

static int g_pass = 0;
static int g_fail = 0;

#define CHECK(cond)                                             \
  do {                                                          \
    if (cond) {                                                 \
      ++g_pass;                                                 \
    } else {                                                    \
      ++g_fail;                                                 \
      printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond);   \
    }                                                           \
  } while (0)

// 测试1：基本 insert / empty / sweep 回调顺序
void test_basic_order() {
  Node a(1), b(2), c(3);
  AtomicIntrusiveLinkedList<Node, &Node::hook> list;

  CHECK(list.empty());
  CHECK(list.insertHead(&a)); // 返回 true：插入后链表中只有这一个元素
  CHECK(!list.insertHead(&b)); // 返回 false：前面已经有 a
  list.insertHead(&c); // 链表现状（头→尾）: c -> b -> a

  CHECK(list.unsafeHead() == &c);
  CHECK(!list.empty());

  // sweep：把整条链摘下后反转，按【尾→头】即插入顺序 a,b,c 回调
  std::vector<int> order;
  list.sweep([&](Node* n) { order.push_back(n->id); });
  CHECK(order == std::vector<int>({1, 2, 3}));
  CHECK(list.empty()); // sweep 之后链表为空（析构前必须清空！）
}

// 测试2：reverseSweep 是 LIFO 顺序；insertHead 断言元素 next 必须为空
void test_reverse_sweep() {
  Node x(10), y(20), z(30);
  AtomicIntrusiveLinkedList<Node, &Node::hook> list;
  list.insertHead(&x);
  list.insertHead(&y);
  list.insertHead(&z);

  // reverseSweep：不反转，按【头→尾】LIFO 回调，即 30,20,10
  std::vector<int> order;
  list.reverseSweep([&](Node* n) { order.push_back(n->id); });
  CHECK(order == std::vector<int>({30, 20, 10}));

  // 摘链后元素的 hook.next 被复位为 nullptr，可再次 insertHead
  list.insertHead(&x);
  CHECK(list.unsafeHead() == &x);
  list.sweep([](Node*) {});
}

// 测试3：多线程无锁压测——4 线程并发 insertHead 各 10000 个，
// 最后单线程 sweep 清点，总数不丢不重
void test_concurrent_produce_consume() {
  constexpr int kThreads = 4;
  constexpr int kPerThread = 10000;
  std::vector<Node> nodes;
  nodes.reserve(kThreads * kPerThread);
  for (int t = 0; t < kThreads; ++t)
    for (int i = 0; i < kPerThread; ++i)
      nodes.emplace_back(i, t);

  AtomicIntrusiveLinkedList<Node, &Node::hook> list;
  std::atomic<int> consumed{0};
  std::vector<std::atomic<int>> perThreadCount(kThreads);
  for (auto& c : perThreadCount) c.store(0);

  std::vector<std::thread> producers;
  for (int t = 0; t < kThreads; ++t) {
    producers.emplace_back([&, t] {
      for (int i = 0; i < kPerThread; ++i) {
        list.insertHead(&nodes[t * kPerThread + i]);
      }
    });
  }

  // 生产者还在跑的时候，消费者可以并发 sweep（sweepOnce 原子摘链）
  std::thread consumer([&] {
    while (consumed.load() < kThreads * kPerThread) {
      list.sweepOnce([&](Node*) {
        ++consumed;
      });
      std::this_thread::yield();
    }
  });

  for (auto& th : producers) th.join();
  consumer.join();
  list.sweep([&](Node*) { ++consumed; }); // 兜底清场

  CHECK(consumed.load() == kThreads * kPerThread);
  CHECK(list.empty());
}

// 测试4：spliceAll —— 把当前元素原子转移给新链表，原链表变空
void test_splice_all() {
  Node a(1), b(2);
  AtomicIntrusiveLinkedList<Node, &Node::hook> list;
  list.insertHead(&a);
  list.insertHead(&b);

  auto moved = list.spliceAll(); // list 变空，元素全在 moved 里
  CHECK(list.empty());
  int n = 0;
  moved.sweep([&](Node*) { ++n; });
  CHECK(n == 2);
}

int main() {
  printf("== folly::AtomicIntrusiveHashMap: 不存在于开源 folly，实测其家族 API ==\n");
  test_basic_order();
  test_reverse_sweep();
  test_concurrent_produce_consume();
  test_splice_all();
  printf("pass=%d fail=%d\n", g_pass, g_fail);
  return g_fail == 0 ? 0 : 1;
}

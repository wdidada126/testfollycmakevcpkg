#include <folly/concurrency/AtomicLinkedList.h>
#include <thread>
#include <vector>
#include <iostream>

// 定义链表节点类型
struct Task {
    int id;
};

folly::AtomicLinkedList<Task> taskList;

void producer(int start, int count) {
    for (int i = start; i < start + count; ++i) {
        Task* task = new Task{.id = i};
        taskList.pushHead(task);
    }
}

void consumer() {
    Task* task = nullptr;
    while ((task = taskList.popHead())) {
        std::cout << "Consuming task ID: " << task->id << std::endl;
        delete task;
    }
}

int main() {
    const int num_tasks_per_producer = 10;
    const int num_producers = 3;

    std::vector<std::thread> producers;
    for (int i = 0; i < num_producers; ++i) {
        producers.emplace_back(producer, i * num_tasks_per_producer, num_tasks_per_producer);
    }

    for (auto& t : producers) {
        t.join();
    }

    // 消费所有任务
    consumer();

    return 0;
}
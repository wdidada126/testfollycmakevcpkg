#include <iostream>
#include <thread>
#include <vector>
#include <folly/synchronization/detail/CLHQueue.h>

void producer(folly::detail::CLHQueue<int>& queue, int id, int count) {
    for (int i = 0; i < count; ++i) {
        queue.enqueue(id * 1000 + i);
        std::cout << "Producer " << id << " enqueued: " << id * 1000 + i << std::endl;
    }
}

void consumer(folly::detail::CLHQueue<int>& queue, int count) {
    for (int i = 0; i < count; ++i) {
        int value;
        while (!queue.try_dequeue(value)) {
            // 可以加一点等待逻辑，比如 yield 或 usleep
            std::this_thread::yield();
        }
        std::cout << "Consumer dequeued: " << value << std::endl;
    }
}

int main() {
    constexpr int num_producers = 3;
    constexpr int items_per_producer = 5;

    folly::detail::CLHQueue<int> queue;

    std::vector<std::thread> producers;
    for (int i = 0; i < num_producers; ++i) {
        producers.emplace_back(producer, std::ref(queue), i, items_per_producer);
    }

    std::thread consumer_thread(consumer, std::ref(queue), num_producers * items_per_producer);

    for (auto& t : producers) {
        t.join();
    }
    consumer_thread.join();

    std::cout << "All done. Queue is empty: " << (queue.empty() ? "yes" : "no") << std::endl;

    return 0;
}
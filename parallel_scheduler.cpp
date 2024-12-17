#include "parallel_scheduler.h"

parallel_scheduler::parallel_scheduler(size_t capacity)
    : capacity(capacity), stop(false) {
    for (size_t i = 0; i < capacity; ++i) {
        threads.emplace_back(&parallel_scheduler::worker, this);
    }
}

parallel_scheduler::~parallel_scheduler() {
    {
        std::lock_guard<std::mutex> lock(tasks_mutex);
        stop = true;
    }
    cv.notify_all();
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void parallel_scheduler::worker() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(tasks_mutex);
            cv.wait(lock, [this](){ return !tasks.empty() || stop; });
            if (stop && tasks.empty()) return;
            task = std::move(tasks.front());
            tasks.pop();
        }
        task();
    }
}


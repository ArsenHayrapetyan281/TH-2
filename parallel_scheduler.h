#ifndef PARALLEL_SCHEDULER_H
#define PARALLEL_SCHEDULER_H

#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

class parallel_scheduler {
public:
    parallel_scheduler(size_t capacity);
    ~parallel_scheduler();
    
    template<typename Function, typename Arg>
    void run(Function&& func, Arg&& arg);

private:
    void worker();
    
    size_t capacity;
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex tasks_mutex;
    std::condition_variable cv;
    bool stop;
};

// Template method definition moved to the header
template<typename Function, typename Arg>
void parallel_scheduler::run(Function&& func, Arg&& arg) {
    {
        std::lock_guard<std::mutex> lock(tasks_mutex);
        tasks.push([func, arg](){ func(arg); });
    }
    cv.notify_one();
}

#endif


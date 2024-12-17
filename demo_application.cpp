#include <iostream>
#include <chrono>
#include "parallel_scheduler.h"

void example_task(int n) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Task " << n << " completed" << std::endl;
}

int main() {
    parallel_scheduler scheduler(3);  // Thread pool with 3 threads
    
    for (int i = 0; i < 10; ++i) {
        scheduler.run(example_task, i);
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(2));  // Give threads time to complete tasks
    
    return 0;
}


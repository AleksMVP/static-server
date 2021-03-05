#pragma once

#include "LockFreeQueue.h"

#include <vector>
#include <thread>
#include <future>
#include <atomic>

template <typename T=std::packaged_task<void(void)>>
class ThreadPool {
 public:
    ThreadPool(size_t threads_number, size_t queue_size) : 
             queue(queue_size), is_working(true) {
        for (size_t i = 0; i < threads_number; i++) {
            threads.push_back(std::thread(std::bind(&ThreadPool::execute, this)));
        }
    }

    ThreadPool(const ThreadPool& rhs) = delete;
    ThreadPool& operator=(const ThreadPool& rhs) = delete;


    void push(T&& task) {
        queue.push_and_wait(std::move(task));
    }

    ~ThreadPool() {
        is_working = false;
        for (auto& thread : threads) {
            thread.join();
        }
    }

 private:
    void execute() {
        while (is_working) {
           T task;
           queue.pop_and_wait(task);
           task();
        }
    }

 private:
    NotLockFreeQueue<T> queue;
    std::atomic<bool> is_working;
    std::vector<std::thread> threads;
};
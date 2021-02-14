#pragma once

#include <queue>
#include <mutex>
#include <atomic>

template <typename T>
class NotLockFreeQueue {
 public:
    explicit NotLockFreeQueue(size_t max_size_) : 
            max_size(max_size_) {}

    NotLockFreeQueue(NotLockFreeQueue&& rhs) : max_size(rhs.max_size) {
        std::lock_guard<std::mutex> m(rhs.mutex);
        queue = std::move(rhs.queue);
    }

    NotLockFreeQueue& operator=(NotLockFreeQueue&& rhs) {
        std::lock_guard<std::mutex> m(rhs.mutex);
        max_size = rhs.max_size;
        queue = std::move(rhs.queue);

        return *this;
    }

    NotLockFreeQueue(const NotLockFreeQueue& rhs) = delete;
    NotLockFreeQueue& operator=(const NotLockFreeQueue& rhs) = delete;

    bool push(T&& item) {
        std::unique_lock<std::mutex> m(mutex);
        if (queue.size() >= max_size) {
            return false;
        }
        queue.push(std::move(item));
        m.unlock();
        cond_var_pop.notify_one();

        return true;
    }

    void push_and_wait(T&& item) {
        std::unique_lock<std::mutex> m(mutex);
        if (queue.size() >= max_size) {
            cond_var_push.wait(m, [this]{return queue.size() < max_size;});
        }
        queue.push(std::move(item));
        m.unlock();
        cond_var_pop.notify_one();
    }

    bool pop(T& item) {
        std::lock_guard<std::mutex> m(mutex);
        if (queue.empty()) {
            return false;
        }
        item = std::move(queue.front());
        queue.pop();

        return true;
    }

    void pop_and_wait(T& item) {
        std::unique_lock<std::mutex> m(mutex);
        if (queue.empty()) {
            cond_var_pop.wait(m, [this]{return !queue.empty();});
        }
        item = std::move(queue.front());
        queue.pop();
        m.unlock();
        cond_var_push.notify_one();
    }

    bool is_empty() const {
        std::lock_guard<std::mutex> m(mutex);
        return queue.empty();
    }

 private:
    std::queue<T> queue;
    size_t max_size;

    mutable std::mutex mutex;
    std::condition_variable cond_var_pop;
    std::condition_variable cond_var_push;
};
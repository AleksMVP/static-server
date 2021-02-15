#pragma once

#include "IHandler.h"
#include "ThreadPool.h"

#include <boost/asio.hpp>

class Server {
 public:
    struct Config {
        Config(int threads_number, int queue_size);
        int queue_size;
        int threads_number;
    };
 public:
    explicit Server(IHandler& handler_, const Config& config);
    void start();
    void stop();

 private:
    std::atomic<bool> is_working;

    IHandler& handler;
    ThreadPool<std::packaged_task<void(void)>> thread_pool;
};
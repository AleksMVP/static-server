#pragma once

#include "IHandler.h"
#include "ThreadPool.h"

#include <boost/asio.hpp>

class Server {
 public:
    explicit Server(IHandler& handler_);
    void start();
    void stop();

 private:
    std::atomic<bool> is_working;

    IHandler& handler;
    ThreadPool<std::packaged_task<void(void)>> thread_pool;
};
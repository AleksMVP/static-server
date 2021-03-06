#pragma once

#include "IHandler.h"
#include "ThreadPool.h"
#include "IAcceptor.h"
#include "Acceptor.h"

template <typename T>
class Server {
 public:
    struct Config {
        Config(int threads_number, int queue_size, int port);
        int threads_number;
        int queue_size;
        int port;
    };

 public:
    explicit Server(
        IHandler<T>& handler_, 
        IAcceptor<T>& acceptor,
        const Config& config, 
        std::ostream& stream
    );
    void start();
    void stop();

 private:
    std::atomic<bool> is_working;
    std::ostream& stream;

    IAcceptor<T>& acceptor;
    IHandler<T>& handler;
    ThreadPool<std::packaged_task<void(void)>> thread_pool;
};


template <typename T>
Server<T>::Server(
        IHandler<T>& handler_, 
        IAcceptor<T>& acceptor,
        const Server<T>::Config& config, 
        std::ostream& stream) : 
    is_working(true),
    stream(stream),
    acceptor(acceptor),
    handler(handler_),  
    thread_pool(config.threads_number, config.queue_size) {}

template <typename T>
void Server<T>::start() {
    is_working = true;
    while(is_working) {
        try {
            T cl(acceptor.accept());
            std::packaged_task<void(void)> task(
                [this, client = std::move(cl)] () mutable {
                    handler.handle(std::move(client));
                }
            );
            thread_pool.push(std::move(task));
        } catch (AcceptException& ex) {
            stream << ex.what() << std::endl;
        }
    }
}

template <typename T>
void Server<T>::stop() {
    is_working = false;
}

template <typename T>
Server<T>::Config::Config(int threads_number, int queue_size, int port) :
        threads_number(threads_number), 
        queue_size(queue_size),
        port(port) {
}
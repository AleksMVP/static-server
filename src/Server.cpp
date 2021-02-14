#include "Server.h"
#include <iostream>

Server::Server(IHandler& handler_) : 
    handler(handler_), is_working(true), thread_pool(2, 2) {}

void Server::start() {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 7888));
    while(is_working) {
        std::unique_ptr<boost::asio::ip::tcp::socket> socket(std::make_unique<boost::asio::ip::tcp::socket>(io_context));
        acceptor.accept(*socket);

        Client cl(std::move(socket));
        std::packaged_task<void(void)> task(
            [this, client = std::move(cl)] () mutable {
                handler.handle(std::move(client));
            }
        );
        thread_pool.push(std::move(task));
    }
}

void Server::stop() {
    is_working = false;
}
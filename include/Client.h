#pragma once 

#include <memory>
#include <boost/asio.hpp>

class Client {
 public:
    explicit Client(std::unique_ptr<boost::asio::ip::tcp::socket> socket);
    Client(const Client& c) = delete;
    Client(Client&& c);

    Client& operator=(Client&& rhs);
    Client& operator=(const Client& rhs) = delete;

    size_t read(char* buffer, size_t size);
    void write(const std::string& data);

    Client& operator<<(const std::string& data);

    ~Client();

 private:
    std::unique_ptr<boost::asio::ip::tcp::socket> socket;
};
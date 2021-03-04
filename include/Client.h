#pragma once 

#include <memory>
#include <boost/asio.hpp>

using tcp = boost::asio::ip::tcp;

class Client {
 public:
    explicit Client(std::unique_ptr<tcp::socket> socket);
    Client(const Client& c) = delete;
    Client(Client&& c);

    Client& operator=(Client&& rhs);
    Client& operator=(const Client& rhs) = delete;

    size_t read(char* buffer, size_t size);
    std::string read_until(const std::string& pattern);

    void write(const std::string& data);
    void write(char* buffer, size_t size);

    Client& operator<<(const std::string& data);

    ~Client();

 private:
    std::unique_ptr<tcp::socket> socket;
};
#include "Client.h"

Client::Client(std::unique_ptr<boost::asio::ip::tcp::socket> socket) : 
    socket(std::move(socket)) {}

Client::Client(Client&& c) {
    socket = std::move(c.socket);
}

Client& Client::operator=(Client&& rhs) {
    socket = std::move(rhs.socket);
    return *this;
}

size_t Client::read(char* buffer, size_t size) {
    boost::system::error_code error;
    int length = socket->read_some(boost::asio::buffer(buffer, size), error);
    if (error == boost::asio::error::eof) {
        return EOF;
    }

    return length;
}

void Client::write(const std::string& data) {
    boost::system::error_code ignored_error;
    boost::asio::write(*socket, boost::asio::buffer(data), ignored_error);
}

Client::~Client() {
    if (socket) {
        socket->close();
    }
}
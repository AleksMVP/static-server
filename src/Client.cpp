#include "Client.h"

Client::Client(int socket) : 
    socket(socket) {}

Client::Client(Client&& c) {
    socket = c.socket;
    c.socket = 0;
}

Client& Client::operator=(Client&& rhs) {
    socket = rhs.socket;
    rhs.socket = 0;
    return *this;
}

void Client::write(char* buffer, size_t size) {
    send(socket, buffer, size, 0); 
}

Client& Client::operator<<(const std::string& data) {
    send(socket , data.c_str(), data.length(), 0); 
    return *this;
}

Client::~Client() {
    if (socket) {
        close(socket);
    }
}
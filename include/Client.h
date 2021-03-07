#pragma once 

#include <memory>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <iostream>
#include <sstream>

#define READ_BUFFER_SIZE 1024

class Client {
 public:
    explicit Client(int socket);
    Client(const Client& c) = delete;
    Client(Client&& c);

    Client& operator=(Client&& rhs);
    Client& operator=(const Client& rhs) = delete;

    template <typename T=std::stringstream>
    std::unique_ptr<T> read_until(const std::string& pattern);

    void write(char* buffer, size_t size);

    Client& operator<<(const std::string& data);

    ~Client();

 private:
    int socket;
};

static char buffer[READ_BUFFER_SIZE];

template <typename T>
std::unique_ptr<T> Client::read_until(const std::string& pattern) {
    std::unique_ptr<T> ss(std::make_unique<T>());

    while (true) {
        int valread = read(socket , buffer, READ_BUFFER_SIZE); 
        *ss << std::string(buffer, valread);
        if (ss->str().find(pattern) != std::string::npos || valread == 0) {
            break;
        }
    }

    return ss;
}
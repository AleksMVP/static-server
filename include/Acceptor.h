#pragma once

#include "IAcceptor.h"

#include <memory>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <iostream>
#include <sstream>

class AcceptException : public std::exception {
 public:
    AcceptException(std::string description) :
            description(std::move(description)) {}

    virtual const char* what() const throw() {
        return description.c_str();
    }

 private:
    std::string description;
};

template <typename T>
class Acceptor : public IAcceptor<T> {
 public:
    explicit Acceptor(int port);

    T accept() override;

 private:
    int server_fd;
    int addrlen;
    sockaddr_in address;
};

template <typename T>
Acceptor<T>::Acceptor(int port) {
    int opt = 1; 
    addrlen = sizeof(address); 
       
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        throw AcceptException("Socket create");
    } 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, 
                                                  &opt, sizeof(opt))) { 
        throw AcceptException("Set sock opt");
    } 

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) { 
        throw AcceptException("Bind failed");
    } 
    if (listen(server_fd, 3) < 0) { 
        throw AcceptException("Listen");
    }  
}

template <typename T>
T Acceptor<T>::accept() { 
    int new_socket;
    if ((new_socket = ::accept(server_fd, (sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) { 
        throw AcceptException("Accept");
    } 

    return T(new_socket);
}
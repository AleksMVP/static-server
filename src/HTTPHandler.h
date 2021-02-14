#pragma once 

#include "IHandler.h"
#include "Client.h"

#define BUFFER_SIZE 1024

class HTTPHandler : public IHandler {
 public: 
    void handle(Client&& data) override;
};
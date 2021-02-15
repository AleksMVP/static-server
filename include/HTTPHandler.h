#pragma once 

#include "IHandler.h"
#include "Client.h"

#define BUFFER_SIZE 1024

class HTTPHandler : public IHandler {
 public: 
    HTTPHandler(const std::string& resolve_path);
    void handle(Client&& data) override;

 private:
    std::string resolve_path;
};
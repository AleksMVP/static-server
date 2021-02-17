#pragma once 

#include "IHandler.h"
#include "Client.h"

#include <filesystem>

#define BUFFER_SIZE 1024

class HTTPHandler : public IHandler {
 public: 
    HTTPHandler(const std::filesystem::path& resolve_path);
    void handle(Client&& data) override;

 private:
    std::filesystem::path resolve_path;
};
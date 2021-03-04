#pragma once 

#include "IHandler.h"
#include "Request.h"
#include "Response.h"

#include <filesystem>
#include <sstream>

#define BUFFER_SIZE 1024

template <typename T>
class HTTPHandler : public IHandler<T> {
 public: 
    HTTPHandler(const std::filesystem::path& resolve_path);
    void handle(T&& data) override;

 private:
    std::filesystem::path resolve_path;
};

template <typename T>
HTTPHandler<T>::HTTPHandler(const std::filesystem::path& resolve_path) : 
        resolve_path(resolve_path) {}

template <typename T>
void HTTPHandler<T>::handle(T&& cl) {
    char buff[BUFFER_SIZE];
    std::stringstream ss;

    while (true) {
        int length = cl.read(buff, BUFFER_SIZE);

        ss << std::string(buff, length);
        if (length == EOF) {
            return;
        } else if (ss.str().find(std::string("\r\n\r\n")) != std::string::npos) {
            std::cout << ss.str() << std::endl;

            Request request(ss);
            Response resp(request, resolve_path);

            cl << resp;

            if (resp.get_content_length() < 1000) {
                std::cout << resp << std::endl;
            }

            return;
        }
    }
}
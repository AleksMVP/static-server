#pragma once 

#include "IHandler.h"
#include "Request.h"
#include "Response.h"

#include <filesystem>
#include <sstream>

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
void HTTPHandler<T>::handle(T&& client) {
    auto result = client.read_until("\r\n\r\n");

    if (!result) {
        return;
    }

    std::istream is(result.get());

    Request request(is);
    Response resp(request, resolve_path);

    client << resp;
}
#pragma once 

#include "IHandler.h"
#include "Request.h"
#include "Response.h"

#include <filesystem>
#include <sstream>

template <typename T>
class HTTPHandler : public IHandler<T> {
 public: 
    HTTPHandler(const std::filesystem::path& resolve_path, std::ostream& stream);
    void handle(T&& data) override;

 private:
    std::filesystem::path resolve_path;
    std::ostream& stream;
};

template <typename T>
HTTPHandler<T>::HTTPHandler(const std::filesystem::path& resolve_path, std::ostream& stream) : 
        resolve_path(resolve_path),
        stream(stream) {}

template <typename T>
void HTTPHandler<T>::handle(T&& client) {
    auto result = client.read_until("\r\n\r\n");

    if (!result) {
        return;
    }

    Request request(*result);
    stream << "---------- Request ----------" << std::endl
           << request                         << std::endl
           << "-----------------------------" << std::endl;

    Response resp(request, resolve_path);
    if (resp.get_content_length() < 200) {
        stream << "---------- Response ----------" << std::endl
               << resp                             << std::endl
               << "------------------------------" << std::endl;
    }

    client << resp;
}
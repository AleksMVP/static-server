#pragma once

#include "Request.h"

#include <string>
#include <memory>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <fstream>

class Response {
 public:
    explicit Response(const Request& request, const std::string& resolve_path);

    size_t get_content_length() const;

    template <typename T>
    friend T& operator<<(T& stream, const Response& resp);

 private:
    void set_date();
    std::string parse_mime(const std::string& s) const;
    void decode_url(std::string::iterator dst, const char *src) const;
    std::string prepare_url(std::string url) const;

    struct Status {
     public:
        explicit Status(int code=200);

     public:
        std::string status;
        unsigned int code;
    };

    std::string protocol;
    Status status;
    std::string date;
    std::string server;
    size_t content_length;
    std::string connection;
    std::string content_type;
    std::shared_ptr<std::istream> body;
};

template <typename T>
T& operator<<(T& stream, const Response& resp) {
    std::stringstream ss;
    ss << resp.protocol << " " << resp.status.code << " " << resp.status.status << "\r\n"
    << "Date: "           << resp.date << "\r\n"
    << "Server: "         << resp.server << "\r\n"
    << "Content-Length: " << resp.content_length << "\r\n"
    << "Connection: "     << resp.connection << "\r\n"
    << "Content-Type: "   << resp.content_type << "\r\n"
    << "\r\n";

    stream << ss.str();

    if (resp.body) {
        std::string tmp;
        while(getline(*resp.body, tmp)) {
            stream << tmp << "\n";
        }
        resp.body->clear();
        resp.body->seekg(0, std::ios::beg);
    }

    return stream;
}

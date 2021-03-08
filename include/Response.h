#pragma once

#include "Request.h"

#include <string>
#include <memory>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <fstream>

#define BUFFER_SIZE (102400)

using Byte = char;

class Response {
 public:
    explicit Response(const Request& request, std::filesystem::path resolve_path);

    size_t get_content_length() const;

    template <typename T>
    friend T& operator<<(T& stream, const Response& resp);

 private:
    std::string parse_mime(const std::string& s) const;
    void decode_url(std::string::iterator dst, const char* src) const;
    std::string prepare_url(std::string url) const;

    struct Status {
     public:
        explicit Status(int code=200);

     public:
        std::string status;
        unsigned int code;
    };

    std::string protocol;
    std::string server;
    std::string connection;
    size_t content_length;
    Status status;
    std::string date;
    std::string content_type;
    std::shared_ptr<std::istream> body;
};

static thread_local Byte buff[BUFFER_SIZE];

template <typename T>
T& operator<<(T& stream, const Response& resp) {
    std::stringstream ss;
    ss  << resp.protocol << " " << resp.status.code    << " " << resp.status.status << "\r\n"
        << "Date: "             << resp.date           << "\r\n"
        << "Server: "           << resp.server         << "\r\n"
        << "Content-Length: "   << resp.content_length << "\r\n"
        << "Connection: "       << resp.connection     << "\r\n"
        << "Content-Type: "     << resp.content_type   << "\r\n"
        << "\r\n";

    stream << ss.str();

    if (resp.body) {
        size_t bytes_count = BUFFER_SIZE * sizeof(Byte); 

        for (unsigned long i = 0; i < resp.content_length / bytes_count; i++) {
            resp.body->read(static_cast<char*>(buff), bytes_count);
            stream.write(static_cast<char*>(buff), bytes_count);
        }
        if (resp.content_length % bytes_count) {
            resp.body->read(static_cast<char*>(buff), resp.content_length % bytes_count);
            stream.write(static_cast<char*>(buff), resp.content_length % bytes_count);
        }

        resp.body->clear();
        resp.body->seekg(0, std::ios::beg);
    }

    return stream;
}

#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <sstream>

struct Response {
    struct Status {
     public:
        Status() {}

        explicit Status(int code) : code(code) {
            switch (code) {
            case 200:
                status = "OK";
                break;
            case 403:
                status = "FORBIDDEN";
                break;
            case 404:
                status = "NOT FOUND";
                break;
            case 405:
                status = "METHOD NOT ALLOWED";
                break;
            }
        }

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

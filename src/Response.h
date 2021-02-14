#pragma once

#include <string>
#include <memory>

struct Response {
    struct Status;
 public:
    Response();
    Response(
        const std::string& protocol,
        const Status&      status,
        const std::string& date,
        const std::string& server,
        size_t             content_length,
        const std::string& connection,
        const std::string& content_type,
        const std::string& body
    );
    Response(
        const std::string& protocol,
        const std::string& date,
        const std::string& server,
        const std::string& connection
    );
    
    std::string str() const;
 public:
    struct Status {
     public:
        Status();
        explicit Status(int code);

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
    std::string body;
};
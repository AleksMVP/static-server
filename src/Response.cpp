#include "Response.h"

#include <sstream>

Response::Status::Status() {}

Response::Status::Status(int code) : code(code) {
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

Response::Response() {}

Response::Response(
        const std::string& protocol,
        const Status&      status,
        const std::string& date,
        const std::string& server,
        size_t             content_length,
        const std::string& connection,
        const std::string& content_type,
        const std::string& body
) : protocol(protocol),
    status(status),
    date(date),
    server(server),
    content_length(content_length),
    connection(connection),
    content_type(content_type),
    body(body) {}

Response::Response(
        const std::string& protocol,
        const std::string& date,
        const std::string& server,
        const std::string& connection
) : protocol(protocol),
    date(date),
    server(server),
    connection(connection) {}

std::string Response::str() const {
    std::stringstream ss;
    ss << protocol << " "    << status.code << " " << status.status << "\r\n"
       << "Date: "           << date << "\r\n"
       << "Server: "         << server << "\r\n"
       << "Content-Length: " << content_length << "\r\n"
       << "Connection: "     << connection << "\r\n"
       << "Content-Type: "   << content_type << "\r\n"
       << "\r\n"
       << body;

    return ss.str();
}
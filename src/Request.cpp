#include "Request.h"

Request::Request(std::istream& stream) {
    std::string tmp;
    stream >> method >> path >> protocol >> host >> host;
}

std::ostream& operator<<(std::ostream& stream, const Request& req) {
    stream << "Method: "   << req.method  << std::endl
           << "Path: "     << req.path << std::endl
           << "Protocol: " << req.protocol << std::endl
           << "Host: "     << req.host;

    return stream;
}

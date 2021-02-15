#pragma once

#include <string>
#include <iostream>

struct Request {
 public:
    explicit Request(std::istream& stream);
    friend std::ostream& operator<<(std::ostream& stream, const Request& req);
 
 public:
    std::string method;
    std::string path;
    std::string protocol;
    std::string host;
};
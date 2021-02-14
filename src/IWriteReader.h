#pragma once

#include <string>

class IWriteReader {
 public:
    virtual size_t read(char* buffer, size_t size) = 0;
    virtual void write(const std::string& data) = 0;
    virtual void write(char* buffer, size_t size) = 0;
};

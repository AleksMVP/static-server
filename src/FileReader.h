#pragma once

#include <string>
#include <optional>

class FileReader {
 public:
    explicit FileReader(const std::string& path);
    std::optional<std::string> read_all() const;

 private:
    std::string path;
};
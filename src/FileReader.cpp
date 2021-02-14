#include "FileReader.h"

#include <fstream>

FileReader::FileReader(const std::string& path) :
        path(path) {}

std::optional<std::string> FileReader::read_all() const {
    std::ifstream file(path);
    if(file.fail()){
        return {};
    }


}
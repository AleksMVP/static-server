#pragma once

#include "Utils.h"

#include <chrono>
#include <ostream>

namespace ch = std::chrono;

template <typename T>
class TimeLogger {
 public:
    explicit TimeLogger(std::ostream& stream) : stream(stream) {
        start = std::chrono::system_clock::now();
    }

    ~TimeLogger() {

        auto end = std::chrono::system_clock::now();
        stream << "Date: " << get_date() << std::endl
               << "Elapsed time: " << ch::duration_cast<T>(end - start).count() << std::endl;
    }
 private:
    std::chrono::system_clock::time_point start;
    std::ostream& stream;
};
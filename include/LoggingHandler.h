#pragma once 

#include "IHandler.h"
#include "TimeLogger.h"

#include <iostream>

template <typename T>
class LoggingHandler : public IHandler<T> {
 public:
    explicit LoggingHandler(IHandler<T>& next_handler_, std::ostream& stream);
    void handle(T&& cl) override;

 private:
    IHandler<T>& next_handler;
    std::ostream& stream;
};

template <typename T>
LoggingHandler<T>::LoggingHandler(IHandler<T>& next_handler_, std::ostream& stream) : 
        next_handler(next_handler_),
        stream(stream) {}

template <typename T>
void LoggingHandler<T>::LoggingHandler::handle(T&& cl) {
    {
        TimeLogger<std::chrono::milliseconds> l(stream);
        next_handler.handle(std::move(cl));
    }
}
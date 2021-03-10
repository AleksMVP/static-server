#pragma once 

#include "IHandler.h"

#include <iostream>

template <typename T>
class ExceptionHandler : public IHandler<T> {
 public:
    explicit ExceptionHandler(IHandler<T>& next_handler_, std::ostream& stream);
    void handle(T&& client) override;

 private:
    IHandler<T>& next_handler;
    std::ostream& stream;
};

template <typename T>
ExceptionHandler<T>::ExceptionHandler(IHandler<T>& next_handler_, std::ostream& stream) : 
        next_handler(next_handler_),
        stream(stream) {}

template <typename T>
void ExceptionHandler<T>::ExceptionHandler::handle(T&& client) {
    try {
        next_handler.handle(std::move(client));
    } catch(std::exception& ex) {
        stream << "Exception: " << ex.what() << std::endl;
    }
}
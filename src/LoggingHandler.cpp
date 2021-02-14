#include "LoggingHandler.h"

LoggingHandler::LoggingHandler(IHandler& next_handler_) : 
        next_handler(next_handler_) {}

void LoggingHandler::handle(Client&& data) {
    std::cout << "Hello LogingHandler" << std::endl;
    next_handler.handle(std::move(data));
}
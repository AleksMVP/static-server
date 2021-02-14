#include "LoggingHandler.h"
#include "TimeLogger.h"

LoggingHandler::LoggingHandler(IHandler& next_handler_) : 
        next_handler(next_handler_) {}

void LoggingHandler::handle(Client&& data) {
    TimeLogger<std::chrono::milliseconds> l(std::cout);
    next_handler.handle(std::move(data));
}
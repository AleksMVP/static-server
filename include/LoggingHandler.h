#pragma once 

#include "IHandler.h"
#include "Client.h"

#include <iostream>

class LoggingHandler : public IHandler {
 public:
    explicit LoggingHandler(IHandler& next_handler_);
    void handle(Client&& cl) override;

 private:
    IHandler& next_handler;
};
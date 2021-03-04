#pragma once 

#include "IHandler.h"
#include "Client.h"

#include <iostream>

class LoggingHandler : public IHandler<Client> {
 public:
    explicit LoggingHandler(IHandler<Client>& next_handler_);
    void handle(Client&& cl) override;

 private:
    IHandler<Client>& next_handler;
};
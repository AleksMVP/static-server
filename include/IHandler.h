#pragma once

#include "Client.h"

class IHandler {
 public:
    virtual void handle(Client&& data) = 0;
    // virtual ~IHandler() = 0;
};
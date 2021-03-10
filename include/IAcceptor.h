#pragma once

template <typename T>
class IAcceptor {
 public:
    virtual T accept() = 0;
    // ~IAcceptor() = 0;
};
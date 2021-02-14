#pragma once

#include "Response.h"
#include "Request.h"

#include <optional>

class ResponseBuilder {
 public:
    explicit ResponseBuilder(const Request& req);
    Response build() const;
 private:
    Request request;
};
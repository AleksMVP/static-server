#pragma once

#include "Response.h"
#include "Request.h"

#include <optional>

class ResponseBuilder {
 public:
    explicit ResponseBuilder(const Request& req);
    Response build();

 private:
    std::string parse_mime(const std::string& s) const;
 
 private:
    Request request;
};
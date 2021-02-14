#include "ResponseBuilder.h"

#include <memory>
#include <filesystem>
#include <fstream>

std::string parse_mime(const std::string& s) {
    if (s == ".html") {
        return "text/html";
    } else if (s == ".js") {
        return "application/javascript";
    } else if (s == ".css") {
        return "text/css";
    } else if (s == ".jpg") {
        return "image/jpeg";
    } else if (s == ".jpeg") {
        return "image/jpeg";
    } else if (s == ".png") {
        return "image/png";
    } else if (s == ".gif") {
        return "image/gif";
    } else if (s == ".swf") {
        return "application/x-shockwave-flash";
    }

    return "none";
}

ResponseBuilder::ResponseBuilder(const Request& request) :
        request(request) {}

Response ResponseBuilder::build() const {
    std::unique_ptr<std::istream> f(std::make_unique<std::ifstream>(request.path));

    Response resp(
        "HTTP/1.1",
        "",
        "Apache/2.2.8 (Ubuntu) mod_ssl/2.2.8 OpenSSL/0.9.8g",
        "Close"
    );

    if (f->fail()) {
        resp.status = Response::Status(404);
        return resp;
    }

    resp.content_type = parse_mime(std::filesystem::path(request.path).extension());

    return resp;
}
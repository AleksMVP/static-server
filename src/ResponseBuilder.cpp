#include "ResponseBuilder.h"

#include <filesystem>
#include <fstream>
#include <chrono>
#include <ctime> 

std::string ResponseBuilder::parse_mime(const std::string& s) const{
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
    std::string filepath = request.path.substr(1, request.path.length());
    if (request.path.substr(request.path.length() - 1, request.path.length()) == "/") {
        filepath += "index.html";
    }

    char time[1000];
    time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm tm = *gmtime(&now);
    strftime(time, sizeof time, "%a, %d %b %Y %H:%M:%S %Z", &tm);

    std::ifstream f(filepath);
    Response resp(
        "HTTP/1.1",
        time,
        "Apache/2.2.8 (Ubuntu) mod_ssl/2.2.8 OpenSSL/0.9.8g",
        "Close"
    );

    if (f.fail()) {
        resp.status = Response::Status(404);
        return resp;
    }
    if (request.method != "HEAD" && request.method != "GET") {
        resp.status = Response::Status(405);
        return resp;
    }

    resp.status = Response::Status(200);

    resp.content_type = parse_mime(std::filesystem::path(filepath).extension());
    if (resp.content_type == "none") {
        resp.status = Response::Status(403);
        return resp;
    }
    resp.body = std::string((std::istreambuf_iterator<char>(f)),
                                std::istreambuf_iterator<char>());
    resp.content_length = resp.body.length();

    return resp;
}
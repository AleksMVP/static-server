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

Response ResponseBuilder::build() {
    int pos = request.path.find("?");
    if (pos != std::string::npos) {
        request.path = request.path.substr(0, pos);
    }

    std::filesystem::path rootpath("/Users/aleks/Desktop/http-test-suite");
    std::filesystem::path filepath = rootpath;
    filepath += std::filesystem::path(request.path);

    bool is_replaced = false;
    if (!filepath.has_filename()) {
        filepath.replace_filename("index.html");
        is_replaced = true;
    }

    char time[1000];
    time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm tm = *gmtime(&now);
    strftime(time, sizeof time, "%a, %d %b %Y %H:%M:%S %Z", &tm);

    Response resp;
    resp.protocol = "HTTP/1.1";
    resp.date = time;
    resp.server = "Apache/2.2.8 (Ubuntu) mod_ssl/2.2.8 OpenSSL/0.9.8g";
    resp.connection = "Close";
    resp.content_length = 0;
    resp.body = nullptr;

    if (request.method != "HEAD" && request.method != "GET") {
        resp.status = Response::Status(405);
        return resp;
    } else if (request.path.find("../") != std::string::npos) {
        resp.status = Response::Status(403);
        return resp;
    }
    {   
        std::cout << filepath << std::endl;
        std::ifstream file(filepath, std::ios::binary | std::ios::ate);
        if (file.fail() && is_replaced) {
            resp.status = Response::Status(403);
            return resp;
        } else if (file.fail()) {
            resp.status = Response::Status(404);
            return resp;
        }
        resp.content_length = file.tellg();
    }

    resp.status = Response::Status(200);
    resp.content_type = parse_mime(filepath.extension());

    if (request.method == "GET") {
        resp.body = std::make_shared<std::ifstream>(std::ifstream(filepath));
        return resp;
    }

    return resp;
}
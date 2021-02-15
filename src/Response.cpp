#include "Response.h"

Response::Response(const Request& request, const std::string& resolve_path) :
            protocol("HTTP/1.1"),
            server("Apache/2.2.8 (Ubuntu) mod_ssl/2.2.8 OpenSSL/0.9.8g"),
            connection("Close"),
            content_length(0),
            body(nullptr) {

    set_date();
    std::filesystem::path filepath(resolve_path);
    filepath += std::filesystem::path(prepare_url(request.path));
    
    std::string tmp = prepare_url(request.path);
    tmp.pop_back();

    if (std::filesystem::path(tmp).extension() != "" && filepath.extension() == "") {
        status = Response::Status(404);
        return;
    }

    bool is_replaced = false;
    if (!filepath.has_filename()) {
        filepath.replace_filename("index.html");
        is_replaced = true;
    }

    if (request.method != "HEAD" && request.method != "GET") {
        status = Response::Status(405);
        return;
    } else if (request.path.find("../") != std::string::npos) {
        status = Response::Status(403);
        return;
    }
    {   
        std::ifstream file(filepath, std::ios::binary | std::ios::ate);
        if (file.fail() && is_replaced) {
            status = Response::Status(403);
            return;
        } else if (file.fail()) {
            status = Response::Status(404);
            return;
        }
        content_length = file.tellg();
    }

    status = Response::Status(200);
    content_type = parse_mime(filepath.extension());
    if (request.method == "GET") {
        body = std::make_shared<std::ifstream>(std::ifstream(filepath));
        return;
    }
}

size_t Response::get_content_length() const {
    return content_length;  
}

Response::Status::Status(int code) : code(code) {
    switch (code) {
    case 200:
        status = "OK";
        break;
    case 403:
        status = "FORBIDDEN";
        break;
    case 404:
        status = "NOT FOUND";
        break;
    case 405:
        status = "METHOD NOT ALLOWED";
        break;
    }
}

std::string Response::parse_mime(const std::string& s) const {
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

void Response::decode_url(std::string::iterator dst, const char *src) const {
    char a, b;
    while (*src) {
        if ((*src == '%') &&
            ((a = src[1]) && (b = src[2])) &&
            (isxdigit(a) && isxdigit(b))) {
                if (a >= 'a')
                        a -= 'a'-'A';
                if (a >= 'A')
                        a -= ('A' - 10);
                else
                        a -= '0';
                if (b >= 'a')
                        b -= 'a'-'A';
                if (b >= 'A')
                        b -= ('A' - 10);
                else
                        b -= '0';
                *dst++ = 16*a+b;
                src+=3;
        } else if (*src == '+') {
                *dst++ = ' ';
                src++;
        } else {
                *dst++ = *src++;
        }
    }
    *dst++ = '\0';
}

void Response::set_date() {
    char time[1000];
    time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm tm = *gmtime(&now);
    strftime(time, sizeof time, "%a, %d %b %Y %H:%M:%S %Z", &tm);

    date = time;
}

std::string Response::prepare_url(std::string url) const  {
    int pos = url.find("?");
    if (pos != std::string::npos) {
        url = url.substr(0, pos);
    }

    std::string decoded_filepath;
    decoded_filepath.resize(url.length());
    decode_url(decoded_filepath.begin(), url.data());

    return decoded_filepath;
}

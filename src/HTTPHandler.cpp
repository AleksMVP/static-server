#include "HTTPHandler.h"
#include "Request.h"
#include "Response.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>

void HTTPHandler::handle(Client&& cl) {
    char buff[BUFFER_SIZE];
    std::stringstream request;
    while (true) {
        int length = cl.read(buff, BUFFER_SIZE);
        request << std::string(buff, length);

        if (length == EOF) {
            return;
        } else if (request.str().find(std::string("\r\n\r\n")) != std::string::npos) {
            Request r(request);
            std::cout << request.str() << std::endl;

            std::unique_ptr<std::ifstream> ss(std::make_unique<std::ifstream>("../main.cpp"));

            Response resp( 
                "HTTP/1.1",
                Response::Status(200),
                "Sun, 10 Oct 2010 23:26:07 GMT",
                "Apache/2.2.8 (Ubuntu) mod_ssl/2.2.8 OpenSSL/0.9.8g",
                12,
                "Close",
                "text/html",
                std::make_unique<std::ifstream>("../main.cpp")
            );

            cl.write(resp.str());
            return;
        }
    }
}

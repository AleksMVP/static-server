#include "HTTPHandler.h"
#include "Request.h"
#include "Response.h"

HTTPHandler::HTTPHandler(const std::string& resolve_path) : 
        resolve_path(resolve_path) {}

void HTTPHandler::handle(Client&& cl) {
    char buff[BUFFER_SIZE];
    std::stringstream ss;

    while (true) {
        int length = cl.read(buff, BUFFER_SIZE);

        ss << std::string(buff, length);
        if (length == EOF) {
            return;
        } else if (ss.str().find(std::string("\r\n\r\n")) != std::string::npos) {
            std::cout << ss.str() << std::endl;

            Request request(ss);
            Response resp(request, resolve_path);

            cl << resp;

            if (resp.get_content_length() < 1000) {
                std::cout << resp << std::endl;
            }

            return;
        }
    }
}

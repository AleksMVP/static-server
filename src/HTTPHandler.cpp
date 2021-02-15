#include "HTTPHandler.h"
#include "Request.h"
#include "Response.h"
#include "ResponseBuilder.h" 

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
            ResponseBuilder res_builder(request);
            Response resp = res_builder.build();

            cl << resp;

            if (resp.content_length < 1000) {
                std::cout << resp << std::endl;
            }

            return;
        }
    }
}

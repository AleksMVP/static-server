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
            Request request(ss);
            std::cout << ss.str() << std::endl;

            ResponseBuilder res_builder(request);

            Response resp = res_builder.build();
            if (resp.content_length < 1000) {
                std::cout << resp.str() << std::endl;
            }

            cl.write(resp.str());
            return;
        }
    }
}

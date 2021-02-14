#include "IHandler.h"
#include "LoggingHandler.h"
#include "HTTPHandler.h"
#include "Server.h"


int main() {
    HTTPHandler http_handler;
    LoggingHandler logging_handler(http_handler);
    Server server(logging_handler);

    server.start();
}
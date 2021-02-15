#include "IHandler.h"
#include "LoggingHandler.h"
#include "HTTPHandler.h"
#include "Server.h"

const std::string RESOLVE_PATH = ".";//"/Users/aleks/Desktop/http-test-suite";
const int queue_size = 10;
const int threads_number = 2;

int main() {
    HTTPHandler http_handler(RESOLVE_PATH);
    LoggingHandler logging_handler(http_handler);
    Server::Config config(
        threads_number, 
        queue_size
    );

    Server server(logging_handler, config);
    server.start();
}
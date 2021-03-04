#include "IHandler.h"
#include "LoggingHandler.h"
#include "HTTPHandler.h"
#include "Server.h"
#include "Client.h"

#include <filesystem>

const std::filesystem::path RESOLVE_PATH = "../tests";
const int QUEUE_SIZE = 10;
const int THREADS_NUMBER = 2;
const int PORT = 7888;

int main() {
    HTTPHandler<Client> http_handler(RESOLVE_PATH);
    LoggingHandler<Client> logging_handler(http_handler);

    Server<Client>::Config config(
        THREADS_NUMBER, 
        QUEUE_SIZE,
        PORT
    );

    Server<Client> server(logging_handler, config);
    server.start();
}
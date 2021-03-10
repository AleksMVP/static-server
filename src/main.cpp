#include "IHandler.h"
#include "LoggingHandler.h"
#include "ExceptionHandler.h"
#include "HTTPHandler.h"
#include "Server.h"
#include "Client.h"

#include <filesystem>

const std::filesystem::path RESOLVE_PATH = "../tests";
const int QUEUE_SIZE = 10;
const int THREADS_NUMBER = 2;
const int PORT = 7888;

int main() {
    Server<Client>::Config config(
        THREADS_NUMBER, 
        QUEUE_SIZE,
        PORT
    );

    Acceptor<Client> acceptor(PORT);

    HTTPHandler<Client> http_handler(RESOLVE_PATH, std::cerr);
    ExceptionHandler<Client> exception_handler(http_handler, std::cerr);
    LoggingHandler<Client> logging_handler(exception_handler, std::cerr);

    Server<Client> server(logging_handler, acceptor, config, std::cerr);

    server.start();
}
#include <blink/Blink.h>

using namespace blink;

int main() {
    core::initLogging("sandbox-server");
    LOG_INFO("Hello world!");

    net::Server server{net::Server::Properties{.port = 5555}};

    server.run();

    return 0;
}

#include "Server.h"

#include "Utils.hpp"

namespace blink::net {

Server::Server(const Properties& props) : m_props(props) {}

awaitable<void> Server::listen() {
    auto executor = co_await coro::executor;
    tcp::acceptor acceptor(executor, {tcp::v4(), m_props.port});

    LOG_INFO("Acceptor serving on {}", toString(acceptor.local_endpoint()));

    while (true) {
        auto socket = co_await acceptor.async_accept(use_awaitable);

        LOG_INFO("Received connection from {}", toString(socket.local_endpoint()));
        co_spawn(executor, onConnection(Connection{std::move(socket)}), detached);
    }
}

void Server::run() {
    try {
        boost::asio::signal_set signals(m_asyncContext, SIGINT, SIGTERM);

        signals.async_wait([&]([[maybe_unused]] auto, [[maybe_unused]] auto) {
            LOG_INFO("Received signal, shutting down server");
            m_asyncContext.stop();
        });

        co_spawn(m_asyncContext, listen(), detached);

        LOG_INFO("Async context starting");
        m_asyncContext.run();

    } catch (std::exception& e) {
        LOG_WARN("Exception: {}", e.what());
    }
}

}  // namespace blink::net

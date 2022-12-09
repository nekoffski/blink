#pragma once

#include "blink/core/Log.h"
#include "Asio.h"

namespace blink::net {

class Server {
   public:
    struct Properties {
        uint16_t port;
    };

    explicit Server(const Properties& props) : m_props(props) {}

    awaitable<void> echo(tcp::socket socket) {
        try {
            char data[1024];
            for (;;) {
                std::size_t n =
                    co_await socket.async_read_some(boost::asio::buffer(data), use_awaitable);
                co_await async_write(socket, boost::asio::buffer(data, n), use_awaitable);
            }
        } catch (std::exception& e) {
            std::printf("echo Exception: %s\n", e.what());
        }
    }

    awaitable<void> listen() {
        auto executor = co_await coro::executor;
        tcp::acceptor acceptor(executor, {tcp::v4(), m_props.port});

        while (true) {
            tcp::socket socket = co_await acceptor.async_accept(use_awaitable);
            co_spawn(executor, echo(std::move(socket)), detached);
        }
    }

    void run() {
        LOG_INFO("Serving HTTP server on {}", m_props.port);

        try {
            boost::asio::signal_set signals(m_asyncContext, SIGINT, SIGTERM);

            signals.async_wait([&]([[maybe_unused]] auto, [[maybe_unused]] auto) {
                m_asyncContext.stop();
            });

            co_spawn(m_asyncContext, listen(), detached);

            m_asyncContext.run();
        } catch (std::exception& e) {
            std::printf("Exception: %s\n", e.what());
        }
    }

   private:
    Properties m_props;

    asio::io_context m_asyncContext;
};

}  // namespace blink::net

#pragma once

#include "blink/core/Log.h"
#include "Asio.h"

#include "Connection.h"

namespace blink::net {

class Server {
   public:
    struct Properties {
        uint16_t port;
    };

    explicit Server(const Properties& props);

    void run();

   private:
    virtual awaitable<void> onConnection(Connection connection) = 0;

    awaitable<void> listen();

    Properties m_props;

    asio::io_context m_asyncContext;
};

}  // namespace blink::net

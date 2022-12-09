#pragma once

#include <string>

#include "Asio.h"

namespace blink::net {

class Connection {
   public:
    explicit Connection(tcp::socket&& socket);

    awaitable<void> sendResponse(const std::string& buffer);
    awaitable<std::string> readRequest();

   private:
    tcp::socket m_socket;
};

}  // namespace blink::net
#include "Connection.h"

#include "blink/core/Log.h"

namespace blink::net {

Connection::Connection(tcp::socket&& socket) : m_socket(std::move(socket)) {}

awaitable<void> Connection::sendResponse(const std::string& buffer) {
    LOG_DEBUG("Sending response:\n{}", buffer);
    co_await async_write(m_socket, asio::buffer(buffer, buffer.size()), use_awaitable);
}

awaitable<std::string> Connection::readRequest() {
    constexpr uint64_t bufferSize = 1024;

    std::string buffer(bufferSize, '\0');
    auto requestLength =
        co_await m_socket.async_read_some(boost::asio::buffer(buffer), use_awaitable);

    LOG_DEBUG("Received request of size {}\n{}", requestLength, buffer);

    co_return buffer;
}

}  // namespace blink::net

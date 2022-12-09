#pragma once

#include <concepts>
#include <string>

#include <fmt/core.h>

#include <boost/asio/ip/address.hpp>

namespace blink::net {

template <typename T>
concept Endpoint = requires(T endpoint) {
    { endpoint.address() } -> std::same_as<boost::asio::ip::address>;
    { endpoint.port() } -> std::same_as<uint16_t>;
};

std::string toString(const Endpoint auto& endpoint) {
    return fmt::format("{}:{}", endpoint.address().to_string(), endpoint.port());
}

}  // namespace blink::net

#pragma once

#include <string>

#include <fmt/core.h>

namespace blink::http {

struct Status {
    uint16_t code;
    std::string message;

    std::string toString() const { return fmt::format("{} {}", code, message); }
};

namespace status {

const Status ok{200, "OK"};
const Status notFound{404, "Not Found"};
const Status badRequest{400, "Bad Request"};
const Status movedPermanently{301, "Moved Permanently"};

}  // namespace status

}  // namespace blink::http
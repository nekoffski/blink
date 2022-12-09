#pragma once

#include <string>
#include <string_view>

#include "Status.h"

namespace blink::http {

constexpr std::string_view httpVersion = "HTTP/1.1";

inline std::string createStatusLine(const Status& status) {
    return fmt::format("{} {}", httpVersion, status.toString());
}

}  // namespace blink::http
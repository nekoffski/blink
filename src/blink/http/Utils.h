#pragma once

#include <string>
#include <string_view>

#include "Status.h"

namespace blink::http {

constexpr std::string_view httpVersion = "HTTP/1.1";

std::string createStatusLine(const Status& status);

}  // namespace blink::http
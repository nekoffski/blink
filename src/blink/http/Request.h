#pragma once

#include <unordered_map>

#include "Method.h"

namespace blink::http {

struct Request {
    Method method;
    std::string path;
    std::string httpVersion;

    std::unordered_map<std::string, std::string> headers;

    static Request parse(const std::string& rawRequest);
};

}  // namespace blink::http
#pragma once

#include <string>

namespace blink::http {

enum class Method { get, post, put };

Method methodFromString(const std::string& method);
std::string toString(Method method);

}  // namespace blink::http
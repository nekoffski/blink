#include "Method.h"

#include <unordered_map>

#include <boost/algorithm/string.hpp>

namespace blink::http {

Method methodFromString(const std::string& method) {
    auto methodUpperCase = boost::to_upper_copy(method);

    static const std::unordered_map<std::string, Method> methods = {
        {"GET",  Method::get },
        {"POST", Method::post}
    };

    if (methods.contains(method))
        return methods.at(method);  // TODO: use find to avoid hashing twice

    throw std::runtime_error{"Unknown method"};
}

std::string toString(Method method) {
    switch (method) {
        case Method::get:
            return "GET";
        case Method::post:
            return "POST";
        case Method::put:
            return "PUT";
        default:
            return "UNKNOWN";
    }
}

}  // namespace blink::http
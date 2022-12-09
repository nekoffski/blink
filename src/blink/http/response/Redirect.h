#pragma once

#include <string>

#include "Response.h"

namespace blink::http::response {

struct Redirect : public Response {
    static std::unique_ptr<Redirect> create(const std::string& location) {
        return std::make_unique<Redirect>(location);
    }

    explicit Redirect(const std::string& location) {
        setHeader("Location", location);
        setStatus(status::movedPermanently);
    }
};

}  // namespace blink::http::response

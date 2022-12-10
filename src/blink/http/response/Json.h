#pragma once

#include "Response.h"
#include "Text.h"

#include <kc/json/Json.h>

namespace blink {

namespace json = kc::json;

namespace http::response {

struct Json : public Text {
    explicit Json(const json::Node& node) : Text(json::toString(node)) {
        setContentType("application/json");
    }

    static std::unique_ptr<Json> create(const json::Node& node) {
        return std::make_unique<Json>(node);
    }
};

}  // namespace http::response
}  // namespace blink

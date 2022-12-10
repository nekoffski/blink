#include "Text.h"

#include "Response.h"

namespace blink::http::response {

Text::Text(const std::string& text) : m_text(text) { setContentType("text/plain; charset=utf-8"); }

awaitable<std::string> Text::getBody([[maybe_unused]] const ResourceInfo&) const {
    co_return m_text;
}

std::unique_ptr<Text> Text::create(const std::string& text) { return std::make_unique<Text>(text); }

}  // namespace blink::http::response

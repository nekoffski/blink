#include "Text.h"

#include "Response.h"

namespace blink::http::response {

Text::Text(const std::string& text) : m_text(text) { setContentType("text/plain; charset=utf-8"); }

std::string Text::getBody([[maybe_unused]] const ResourceInfo&) const { return m_text; }

std::unique_ptr<Text> Text::create(const std::string& text) { return std::make_unique<Text>(text); }

}  // namespace blink::http::response

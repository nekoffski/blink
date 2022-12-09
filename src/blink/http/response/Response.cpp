#include "Response.h"

#include <sstream>

namespace blink::http::response {

Response::Response() : m_status(status::ok) {}

std::string Response::get(const ResourceInfo& resourceInfo) const {
    const auto statusLine = createStatusLine(m_status);
    const auto body       = getBody(resourceInfo);

    if (const auto bodySize = body.size(); bodySize > 0)
        m_headers["Content-Length"] = std::to_string(bodySize);

    std::stringstream headersStream;
    for (const auto& [key, value] : m_headers) headersStream << key << ": " << value << '\n';

    auto headers = headersStream.str();
    headers.pop_back();  // remove last \n

    return fmt::format("{}\n{}\r\n\r\n{}", statusLine, headers, body);
}

std::string Response::getBody([[maybe_unused]] const ResourceInfo&) const { return ""; }

void Response::setStatus(const Status& status) { m_status = status; }

void Response::setHeader(const std::string& key, const std::string& value) {
    m_headers[key] = value;
}

void Response::setHeader(const std::string& key, int value) {
    m_headers[key] = std::to_string(value);
}
void Response::setContentType(const std::string& mime) { setHeader("Content-Type", mime); }

}  // namespace blink::http::response

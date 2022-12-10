#include "Html.h"

#include <kc/core/FileSystem.h>

#include "blink/async/Delegate.hpp"

namespace blink::http::response {

Html::Html() { setContentType("text/html; charset=utf-8"); }

std::unique_ptr<Html> Html::fromText(const std::string& text) {
    return std::make_unique<detail::HtmlTextResponse>(text);
}

std::unique_ptr<Html> Html::fromFile(const std::string& path) {
    return std::make_unique<detail::HtmlFileResponse>(path);
}

namespace detail {

HtmlTextResponse::HtmlTextResponse(const std::string& text) : m_text(text) {}

awaitable<std::string> HtmlTextResponse::getBody([[maybe_unused]] const ResourceInfo&) const {
    co_return m_text;
}

HtmlFileResponse::HtmlFileResponse(const std::string& path) : m_path(path) {}

awaitable<std::string> HtmlFileResponse::getBody(const ResourceInfo& resourceInfo) const {
    const auto fullPath = fmt::format("{}/{}", resourceInfo.resourcePath, m_path);

    co_await_return async::delegateToThread([&fullPath]() -> std::string {
        return kc::core::FileSystem{}.readFile(fullPath);
    });
}

}  // namespace detail

}  // namespace blink::http::response

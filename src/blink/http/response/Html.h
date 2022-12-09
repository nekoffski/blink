#pragma once

#include <string>

#include "Response.h"

namespace blink::http::response {

struct Html : public Response {
    explicit Html();

    static std::unique_ptr<Html> fromText(const std::string& text);
    static std::unique_ptr<Html> fromFile(const std::string& path);
};

namespace detail {

class HtmlTextResponse : public Html {
   public:
    explicit HtmlTextResponse(const std::string& text);

    std::string getBody(const ResourceInfo& resourceInfo) const override;

   private:
    std::string m_text;
};

class HtmlFileResponse : public Html {
   public:
    explicit HtmlFileResponse(const std::string& path);

    std::string getBody(const ResourceInfo& resourceInfo) const override;

   private:
    std::string m_path;
};

}  // namespace detail

}  // namespace blink::http::response
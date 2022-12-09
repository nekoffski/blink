#pragma once

#include "Response.h"

namespace blink::http::response {

class Text : public Response {
   public:
    static std::unique_ptr<Text> create(const std::string& text);

    explicit Text(const std::string& text);

   private:
    std::string getBody(const ResourceInfo& resourceInfo) const override;

    std::string m_text;
};

}  // namespace blink::http::response
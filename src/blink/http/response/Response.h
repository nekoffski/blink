#pragma once

#include <memory>
#include <unordered_map>

#include "blink/net/Asio.h"
#include "blink/http/Status.h"
#include "blink/http/Utils.h"
#include "blink/http/ResourceInfo.h"

namespace blink::http::response {

class Response {
   public:
    explicit Response();

    awaitable<std::string> get(const ResourceInfo& resourceInfo) const;

    void setStatus(const Status& status);
    void setHeader(const std::string& key, const std::string& value);
    void setHeader(const std::string& key, int value);
    void setContentType(const std::string& mime);

   private:
    virtual awaitable<std::string> getBody(const ResourceInfo& resourceInfo) const;

    Status m_status;
    mutable std::unordered_map<std::string, std::string> m_headers;
};

}  // namespace blink::http::response

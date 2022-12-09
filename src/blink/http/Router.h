#pragma once

#include <functional>
#include <unordered_map>

#include "blink/net/Asio.h"
#include "response/Response.h"
#include "Request.h"

namespace blink::http {

struct Route {
    using Return   = awaitable<std::unique_ptr<response::Response>>;
    using Callback = std::function<Return(const Request&)>;

    std::string path;
    Callback callback;
};

class Router {
   public:
    explicit Router(const std::string& path = "/");

    void addRoute(const std::string& path, const Route::Callback& callback);
    void addRoute(const Route& route);

    bool hasRouteFor(const std::string& path) const;
    const Route::Callback& getHandler(const std::string& path) const;

   private:
    std::unordered_map<std::string, Route::Callback> m_routes;
};

}  // namespace blink::http

#pragma once

#include <functional>
#include <unordered_map>

#include "blink/net/Asio.h"
#include "response/Response.h"
#include "Request.h"

namespace blink::http {

struct Route {
    using Return  = awaitable<std::unique_ptr<response::Response>>;
    using Handler = std::function<Return(const Request&)>;

    std::string path;
    Handler handler;
};

class Router {
   public:
    explicit Router(const std::string& path = "/");

    void addRoute(const std::string& path, const Route::Handler& handler);
    void addRoute(const Route& route);

    bool hasRouteFor(const std::string& path) const;
    const Route::Handler& getHandler(const std::string& path) const;

   private:
    std::unordered_map<std::string, Route::Handler> m_routes;
};

}  // namespace blink::http

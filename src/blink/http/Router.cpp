#include "Router.h"

#include <kc/core/Log.h>

namespace blink::http {

Router::Router(const std::string& path) {}

void Router::addRoute(const std::string& path, const Route::Callback& callback) {
    ASSERT(not m_routes.contains(path), "Route for {} is already specified", path);
    m_routes[path] = callback;
}

void Router::addRoute(const Route& route) { addRoute(route.path, route.callback); }

bool Router::hasRouteFor(const std::string& path) const { return m_routes.contains(path); }

const Route::Callback& Router::getHandler(const std::string& path) const {
    return m_routes.at(path);
}

}  // namespace blink::http

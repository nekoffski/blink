#include "Server.h"

#include "response/Text.h"

namespace blink::http {

void Server::addRouter(Router* router) { m_routers.push_back(router); }

void Server::setResourcePath(const std::string& path) { m_resourceInfo.resourcePath = path; }

const ResourceInfo* Server::getResourceInfo() const { return &m_resourceInfo; }

awaitable<void> Server::onConnection(net::Connection connection) {
    try {
        auto request = co_await readRequest(connection);

        LOG_INFO(
            "Received request on '{}', method {}, HTTP version {}", request.path,
            toString(request.method), request.httpVersion
        );

        if (not co_await findRoute(request, connection)) {
            response::Text response{"Url not found"};
            response.setStatus(http::status::notFound);

            co_await connection.sendResponse(co_await response.get(m_resourceInfo));
        }

    } catch (std::exception& e) {
        LOG_WARN("Connection processing error: {}", e.what());
    }
}

awaitable<bool> Server::findRoute(const Request& request, net::Connection& connection) {
    LOG_DEBUG("Looking for a valid route");

    for (auto& router : m_routers) {
        if (router->hasRouteFor(request.path)) {  // TODO: use find to avoid hashing string twice
            LOG_DEBUG("Route found, invoking callback");

            auto response = co_await std::invoke(router->getHandler(request.path), request);
            co_await connection.sendResponse(co_await response->get(m_resourceInfo));

            co_return true;
        }
    }

    co_return false;
}

awaitable<Request> Server::readRequest(net::Connection& connection) {
    co_return Request::parse(co_await connection.readRequest());
}

}  // namespace blink::http

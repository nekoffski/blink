#include "Server.h"

#include "response/Text.h"

namespace blink::http {

void Server::addRouter(Router* router) { m_routers.push_back(router); }

void Server::setResourcePath(const std::string& path) { m_resourceInfo.resourcePath = path; }

awaitable<void> Server::onConnection(net::Connection connection) {
    try {
        auto request = co_await readRequest(connection);

        LOG_INFO(
            "Received request on '{}', method {}, HTTP version {}", request.path,
            toString(request.method), request.httpVersion
        );

        LOG_DEBUG("Looking for a valid route");

        for (auto& router : m_routers) {
            if (router->hasRouteFor(request.path)) {
                LOG_DEBUG("Route found, invoking callback");

                auto handler  = router->getHandler(request.path);
                auto response = co_await handler(request);

                co_await connection.sendResponse(response->get(m_resourceInfo));

                co_return;
            }
        }

        // handle 404
        response::Text response{"Url not found"};
        response.setStatus(http::status::notFound);

        co_await connection.sendResponse(response.get(m_resourceInfo));

    } catch (std::exception& e) {
        LOG_WARN("Connection processing error: {}", e.what());
    }
}

awaitable<Request> Server::readRequest(net::Connection& connection) {
    co_return Request::parse(co_await connection.readRequest());
}

}  // namespace blink::http

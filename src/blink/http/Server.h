#pragma once

#include <vector>

#include "blink/net/Server.h"

#include "Request.h"
#include "Router.h"
#include "ResourceInfo.h"

namespace blink::http {

class Server : public net::Server {
   public:
    using Properties = net::Server::Properties;
    using net::Server::Server;

    void addRouter(Router* router);
    void setResourcePath(const std::string& path);

   private:
    awaitable<void> onConnection(net::Connection connection) override;
    awaitable<Request> readRequest(net::Connection& connection);

    std::vector<Router*> m_routers;
    ResourceInfo m_resourceInfo;
};

}  // namespace blink::http
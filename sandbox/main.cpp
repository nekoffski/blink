#include <kc/core/FileSystem.h>

#include <blink/Blink.h>
#include <blink/Responses.h>

using namespace blink;

namespace response = http::response;

int main() {
    core::initLogging("sandbox-server");

    kc::core::FileSystem fs{};

    http::Server server{http::Server::Properties{.port = 5555}};
    http::Router root;

    root.addRoute(http::Route{
        .path = "/", .handler = [&](const http::Request& request) -> http::Route::Return {
            if (request.method == http::Method::get)
                co_return response::Html::fromText("<h1>Hello world!</h1>");
            else if (request.method == http::Method::post)
                co_return response::Html::fromText("<h1>Nothing to insert here!</h1>");

            auto response = response::Text::create("Method not handled");

            response->setStatus(http::status::badRequest);
            co_return response;
        }});

    root.addRoute(http::Route{
        .path = "/home", .handler = [&](const http::Request& request) -> http::Route::Return {
            co_return response::Html::fromFile("html/index.html");
        }});

    root.addRoute(http::Route{
        .path    = "/old",
        .handler = [&]([[maybe_unused]] const http::Request&) -> http::Route::Return {
            co_return response::Redirect::create("/home");
        }});

    root.addRoute(http::Route{
        .path    = "/data",
        .handler = [&]([[maybe_unused]] const http::Request&) -> http::Route::Return {
            const auto dataPath =
                fmt::format("{}/{}", server.getResourceInfo()->resourcePath, "json/data.json");

            const auto jsonContent = co_await async::TaskExecutor<>::callInThread([&]() {
                return json::loadJson(fs.readFile(dataPath));
            });

            co_return response::Json::create(jsonContent);
        }});

    server.setResourcePath("/home/nek0/kapik/projects/blink/sandbox/res");
    server.addRouter(&root);
    server.run();

    return 0;
}

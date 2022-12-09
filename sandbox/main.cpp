#include <blink/Blink.h>
#include <blink/Responses.h>

using namespace blink;

namespace response = http::response;

int main() {
    core::initLogging("sandbox-server");

    http::Server server{http::Server::Properties{.port = 5555}};
    http::Router root;

    root.addRoute(http::Route{
        .path = "/", .callback = [](const http::Request& request) -> http::Route::Return {
            if (request.method == http::Method::get)
                co_return response::Html::fromText("<h1>Hello world!</h1>");
            else if (request.method == http::Method::post)
                co_return response::Html::fromText("<h1>Nothing to insert here!</h1>");

            auto response = response::Text::create("Method not handled");

            response->setStatus(http::status::badRequest);
            co_return response;
        }});

    root.addRoute(http::Route{
        .path = "/home", .callback = [](const http::Request& request) -> http::Route::Return {
            co_return response::Html::fromFile("index.html");
        }});

    root.addRoute(http::Route{
        .path     = "/old",
        .callback = []([[maybe_unused]] const http::Request&) -> http::Route::Return {
            co_return response::Redirect::create("/home");
        }});

    server.setResourcePath("/home/nek0/kapik/projects/blink/sandbox/html");
    server.addRouter(&root);
    server.run();

    return 0;
}

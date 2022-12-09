#include "Request.h"

#include <kc/core/String.h>
#include <kc/core/Utils.hpp>

#include "blink/core/Log.h"

namespace blink::http {

Request Request::parse(const std::string& rawRequest) {
    using namespace kc::core;

    auto requestLines = split(rawRequest, '\n');
    auto status       = split(requestLines[0], ' ');

    ASSERT(status.size() == 3, "Received invalid HTTP status - {}", requestLines[0]);

    Request request;

    request.method      = methodFromString(status[0]);
    request.path        = status[1];
    request.httpVersion = status[2];

    static constexpr char headerSeparator = ':';

    for (int i = 1; i < requestLines.size(); ++i) {
        const auto header = split(requestLines[i], headerSeparator);

        if (header.size() == 2) request.headers[header[0]] = header[1].substr(1);
    }

    return request;
}

}  // namespace blink::http
#include "Utils.h"

namespace blink::http {

std::string createStatusLine(const Status& status) {
    return fmt::format("{} {}", httpVersion, status.toString());
}

}  // namespace blink::http
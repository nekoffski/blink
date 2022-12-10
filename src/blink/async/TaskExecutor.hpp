#pragma once

#include <functional>
#include <future>
#include <thread>
#include <chrono>

#include <kc/async/Future.hpp>

#include "blink/core/Log.h"
#include "blink/net/Asio.h"

namespace blink::async {

template <typename T>
concept ExecutorType = requires {
    {T{[]() {}}};
};

template <ExecutorType Executor = std::jthread> struct TaskExecutor {
    template <typename F, typename... Args>
    static awaitable<std::result_of_t<F(Args...)>> callInThread(F&& f, Args&&... args) {
        using namespace std::chrono_literals;
        using kc::async::Future;
        using Return = std::result_of_t<F(Args...)>;

        std::packaged_task<Return()> task([&]() { return f(std::forward<Args>(args)...); });
        auto future = Future{task.get_future()};

        Executor executor([&task]() { task(); });

        static const auto sleepInterval = 50ms;
        boost::asio::steady_timer timer(co_await coro::executor);

        while (not future.isReady()) {
            timer.expires_from_now(sleepInterval);
            co_await timer.async_wait(use_awaitable);
        }

        co_return future.getValue();
    }
};

}  // namespace blink::async

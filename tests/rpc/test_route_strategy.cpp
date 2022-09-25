#include "skyrpc/rpc/route_strategy.h"

#include "skyrpc/log.h"
static skyrpc::Logger::ptr g_logger = SKYRPC_LOG_ROOT();
std::vector<int> list{1, 2, 3, 4, 5};

void test_random() {
    skyrpc::rpc::RouteStrategy<int>::ptr strategy =
            skyrpc::rpc::RouteEngine<int>::queryStrategy(skyrpc::rpc::Strategy::Random);

    SKYRPC_LOG_DEBUG(g_logger) << "random";
    for ([[maybe_unused]] auto i: list) {
        auto a = strategy->select(list);
        SKYRPC_LOG_DEBUG(g_logger) << a;
    }
}

void test_poll() {
    skyrpc::rpc::RouteStrategy<int>::ptr strategy =
            skyrpc::rpc::RouteEngine<int>::queryStrategy(skyrpc::rpc::Strategy::Polling);

    SKYRPC_LOG_DEBUG(g_logger) << "Poll";
    for ([[maybe_unused]] auto i: list) {
        auto a = strategy->select(list);
        SKYRPC_LOG_DEBUG(g_logger) << a;
    }
}
void test_hash() {
    skyrpc::rpc::RouteStrategy<int>::ptr strategy =
            skyrpc::rpc::RouteEngine<int>::queryStrategy(skyrpc::rpc::Strategy::HashIP);

    SKYRPC_LOG_DEBUG(g_logger) << "Hash";
    for ([[maybe_unused]] auto i: list) {
        auto a = strategy->select(list);
        SKYRPC_LOG_DEBUG(g_logger) << a;
    }
}
int main() {
    test_random();
    test_poll();
    test_hash();
}
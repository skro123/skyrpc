#include "skyrpc/rpc/rpc_service_registry.h"

void rpc_service_registry() {
    skyrpc::Address::ptr address = skyrpc::Address::LookupAny("127.0.0.1:8070");
    skyrpc::rpc::RpcServiceRegistry::ptr server(new skyrpc::rpc::RpcServiceRegistry());
    while (!server->bind(address)){
        sleep(1);
    }
    server->start();
}
void test_publish() {
    skyrpc::Address::ptr address = skyrpc::Address::LookupAny("127.0.0.1:8070");
    skyrpc::rpc::RpcServiceRegistry::ptr server(new skyrpc::rpc::RpcServiceRegistry());
    while (!server->bind(address)){
        sleep(1);
    }
    server->start();
    Go {
        int n = 0;
        std::vector<int> vec;
        while (true) {
            vec.push_back(n);
            sleep(3);
            server->publish("data", vec);
            ++n;
        }
    };
}
int main() {
    go test_publish;
}
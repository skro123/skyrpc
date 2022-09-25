#include "skyrpc/rpc/rpc_service_registry.h"

// 服务注册中心
void Main() {
    skyrpc::Address::ptr address = skyrpc::Address::LookupAny("192.168.147.129:8080");
    skyrpc::rpc::RpcServiceRegistry::ptr server = std::make_shared<skyrpc::rpc::RpcServiceRegistry>();
    // 服务注册中心绑定在8080端口
    while (!server->bind(address)){
        sleep(1);
    }
    server->start();
}

int main() {
    go Main;
}
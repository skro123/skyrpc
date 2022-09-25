#include "skyrpc/rpc/rpc_server.h"

int add(int a,int b){
    return a + b;
}

// 向服务中心注册服务，并处理客户端请求
void Main() {
    int port = 9001;
    skyrpc::Address::ptr local = skyrpc::IPv4Address::Create("192.168.147.129",port);
    // skyrpc::Address::ptr registry = skyrpc::Address::LookupAny("127.0.0.1:8080");
    skyrpc::Address::ptr registry = skyrpc::Address::LookupAny("192.168.147.129:8080");

    skyrpc::rpc::RpcServer::ptr server = std::make_shared<skyrpc::rpc::RpcServer>();;

    // 注册服务，支持函数指针和函数对象，支持标准库容器
    server->registerMethod("add",add);
    server->registerMethod("echo", [](std::string str){
        return str;
    });
    server->registerMethod("revers", [](std::vector<std::string> vec) -> std::vector<std::string>{
        std::reverse(vec.begin(), vec.end());
        return vec;
    });

    // 先绑定本地地址
    while (!server->bind(local)){
        port = port + 1;
        local = skyrpc::IPv4Address::Create("127.0.0.1",port);
        sleep(1);
    }
    // 绑定服务注册中心
    server->bindRegistry(registry);
    // 开始监听并处理服务请求
    server->start();
}

int main() {
    go Main;
}
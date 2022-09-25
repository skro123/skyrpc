#include "skyrpc/rpc/rpc_connection_pool.h"
#include "skyrpc/rpc/serializer.h"
#include "skyrpc/log.h"
static skyrpc::Logger::ptr g_logger = SKYRPC_LOG_ROOT();

void test_call() {
    skyrpc::Address::ptr address = skyrpc::Address::LookupAny("127.0.0.1:8070");
    //skyrpc::rpc::RpcConnectionPool::ptr con = std::make_shared<skyrpc::rpc::RpcConnectionPool>(5);
    skyrpc::rpc::RpcConnectionPool::ptr con = std::make_shared<skyrpc::rpc::RpcConnectionPool>();
    con->connect(address);

//    auto aa = con->call<int>("add",1,1);
//    SKYRPC_LOG_INFO(g_logger) << aa.toString();
//    aa = con->call<int>("add",2,2);
//    SKYRPC_LOG_INFO(g_logger) << aa.toString();
//    aa = con->call<int>("add",3,3);
//    SKYRPC_LOG_INFO(g_logger) << aa.toString();
    //std::future<skyrpc::rpc::Result<std::string>> b = con->async_call<std::string>("getStr");

    std::vector<std::string> vec{"a-","b-","c"};
    con->callback("CatString", vec, [](skyrpc::rpc::Result<std::string> str){
        SKYRPC_LOG_INFO(g_logger) << str.toString();
    });
    con->callback("CatString", vec, [](skyrpc::rpc::Result<std::string> str){
        SKYRPC_LOG_INFO(g_logger) << str.toString();
    });
    //sleep(4);
    int n=0;
    while (n!=10000) {
        SKYRPC_LOG_DEBUG(g_logger) << n++;
        con->callback("add", 0, n, [](skyrpc::rpc::Result<int> res){
            SKYRPC_LOG_DEBUG(g_logger) << res.toString();
        });
//        auto rt = con->call<int>("add",0,n);
//        SKYRPC_LOG_DEBUG(g_logger) << rt.toString();
    }
    //sleep(5);
//    SKYRPC_LOG_INFO(g_logger) << b.get().toString();
//    SKYRPC_LOG_INFO(g_logger) << a.get().toString();
}

void test_subscribe() {
    skyrpc::Address::ptr address = skyrpc::Address::LookupAny("127.0.0.1:8070");
    //skyrpc::rpc::RpcConnectionPool::ptr con = std::make_shared<skyrpc::rpc::RpcConnectionPool>(5);
    skyrpc::rpc::RpcConnectionPool::ptr con = std::make_shared<skyrpc::rpc::RpcConnectionPool>();
    con->connect(address);
    con->subscribe("data",[](skyrpc::rpc::Serializer s){
        std::vector<int> vec;
        s >> vec;
        std::string str;
        std::for_each(vec.begin(), vec.end(),[&str](int i) mutable { str += std::to_string(i);});
        LOG_DEBUG << "recv publish: " << str;
    });
    while (true) {
        sleep(5);
    }
}

void test_subscribe_service() {
    skyrpc::Address::ptr address = skyrpc::Address::LookupAny("127.0.0.1:8070");
    skyrpc::rpc::RpcConnectionPool::ptr con = std::make_shared<skyrpc::rpc::RpcConnectionPool>();
    con->connect(address);

    auto aa = con->call<int>("add",1,1);
    SKYRPC_LOG_INFO(g_logger) << aa.toString();

    while (true) {
        // 将 test_rpc_server 断开，会看到控制台打印 service [ add : 127.0.0.1:8080 ] quit
        // 将 test_rpc_server 重新连接，会看到控制台打印 service [ add : 127.0.0.1:8080 ] join
        // 实时的发布/订阅模式实现自动维护服务列表
        sleep(1);
    }
}

int main() {
    //go test_subscribe;
    go test_subscribe_service;
}
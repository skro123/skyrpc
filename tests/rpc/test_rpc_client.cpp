#include "skyrpc/rpc/rpc_client.h"
#include "skyrpc/io_manager.h"
#include "skyrpc/log.h"
static skyrpc::Logger::ptr g_logger = SKYRPC_LOG_ROOT();

void test1() {
    skyrpc::Address::ptr address = skyrpc::Address::LookupAny("127.0.0.1:8080");
    skyrpc::rpc::RpcClient::ptr client(new skyrpc::rpc::RpcClient());

    if (!client->connect(address)) {
        SKYRPC_LOG_DEBUG(g_logger) << address->toString();
        return;
    }
    int n=0;
    //std::vector<std::future<skyrpc::rpc::Result<int>>> vec;
    while (n!=1000) {
        //SKYRPC_LOG_DEBUG(g_logger) << n++;
        n++;
        client->callback("sleep", [](skyrpc::rpc::Result<> res) {
            SKYRPC_LOG_DEBUG(g_logger) << res.toString();
        });
    }
    auto rt = client->call<int>("add", 0, n);
    SKYRPC_LOG_DEBUG(g_logger) << rt.toString();
    //sleep(3);
    //client->close();
    client->setTimeout(1000);
    auto sl = client->call<void>("sleep");
    SKYRPC_LOG_DEBUG(g_logger) << "sleep 2s " << sl.toString();

}
void subscribe() {
    skyrpc::Address::ptr address = skyrpc::Address::LookupAny("127.0.0.1:8080");
    skyrpc::rpc::RpcClient::ptr client(new skyrpc::rpc::RpcClient());

    if (!client->connect(address)) {
        SKYRPC_LOG_DEBUG(g_logger) << address->toString();
        return;
    }
    client->subscribe("iloveyou",[](skyrpc::rpc::Serializer s){
        std::string str;
        s >> str;
        LOG_DEBUG << str;
    }) ;
    while(true)
    sleep(100);
}
// 测试重连
void test_retry() {
    skyrpc::Address::ptr address = skyrpc::Address::LookupAny("127.0.0.1:8080");
    skyrpc::rpc::RpcClient::ptr client(new skyrpc::rpc::RpcClient());

    if (!client->connect(address)) {
        SKYRPC_LOG_DEBUG(g_logger) << address->toString();
        return;
    }
    client->close();
    //client = std::make_shared<skyrpc::rpc::RpcClient>();

    if (!client->connect(address)) {
        SKYRPC_LOG_DEBUG(g_logger) << address->toString();
        return;
    }
    int n=0;
    //std::vector<std::future<skyrpc::rpc::Result<int>>> vec;
    while (n!=1000) {
        sleep(2);
        //SKYRPC_LOG_DEBUG(g_logger) << n++;
        n++;
        auto res = client->call<int>("add",1,n);
        if (res.getCode() == skyrpc::rpc::RpcState::RPC_CLOSED) {
            //client = std::make_shared<skyrpc::rpc::RpcClient>();
            if (!client->connect(address)) {
                SKYRPC_LOG_DEBUG(g_logger) << address->toString();
            }
            res = client->call<int>("add",1,n);
        }
        LOG_DEBUG << res.toString();

    }
}
int main() {
    go test1;
    //go subscribe;
    go test_retry;
}

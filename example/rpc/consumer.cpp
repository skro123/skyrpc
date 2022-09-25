#include "skyrpc/log.h"
#include "skyrpc/rpc/rpc_connection_pool.h"
#include <time.h>

static skyrpc::Logger::ptr g_logger = SKYRPC_LOG_ROOT();

// 连接服务中心，自动服务发现，执行负载均衡决策，同时会缓存发现的结果
void Main() {
    skyrpc::Address::ptr registry = skyrpc::Address::LookupAny("192.168.147.129:8080");

    // 设置连接池的数量
    skyrpc::rpc::RpcConnectionPool::ptr con = std::make_shared<skyrpc::rpc::RpcConnectionPool>();

    // 连接服务中心
    con->connect(registry);

    skyrpc::rpc::Result<int> res;

    // 第一种调用接口，以同步的方式异步调用，原理是阻塞读时会在协程池里调度
    res = con->call<int>("add", 123, 321);
    SKYRPC_LOG_INFO(g_logger) << res.getVal();

    // 第二种调用接口，调用时会立即返回一个channel
    auto chan = con->async_call<int>("add", 123, 321);
    chan >> res;
    SKYRPC_LOG_INFO(g_logger) << res.getVal();

    // 第三种调用接口，异步回调
    con->callback("add", 114514, 114514, [](skyrpc::rpc::Result<int> res){
        SKYRPC_LOG_INFO(g_logger) << res.getVal();
    });
    time_t start, end;
    // 测试并发
    int n=0;
    start = clock();
    while(n != 100) {
        n++;
        // con->callback("add", 0, n, [](skyrpc::rpc::Result<int> res){
        //     // SKYRPC_LOG_INFO(g_logger) << res.getVal();
        // });
        con->call<int>("add", 0, n);
    }
    // 异步接口必须保证在得到结果之前程序不能退出
    sleep(3);
    end = clock();
    std::cout<<"DBSCAN time: "<<(end-start)/1000<<" ms"<<std::endl;         // time.h计时
}

int main() {
    go Main;
}
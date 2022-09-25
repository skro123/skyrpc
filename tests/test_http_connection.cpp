#include <fstream>
#include "skyrpc/skyrpc.h"
static skyrpc::Logger::ptr g_logger = SKYRPC_LOG_ROOT();
void run(){
    skyrpc::Address::ptr addr = skyrpc::IPAddress::Create("www.baidu.com", 80);
    if(!addr) {
        SKYRPC_LOG_INFO(g_logger) << "get addr error";
        return;
    }

    skyrpc::Socket::ptr sock = skyrpc::Socket::CreateTCP(addr);
    bool rt = sock->connect(addr);
    if(!rt) {
        SKYRPC_LOG_INFO(g_logger) << "connect " << addr->toString() << " failed";
        return;
    }

    skyrpc::http::HttpConnection::ptr conn(new skyrpc::http::HttpConnection(sock));
    skyrpc::http::HttpRequest::ptr req(new skyrpc::http::HttpRequest);
    req->setPath("/index");
    req->setHeader("host", "www.baidu.com");
    SKYRPC_LOG_INFO(g_logger) << "req:" << std::endl
                             << req->toString();
    int n = conn->sendRequest(req);
    SKYRPC_LOG_INFO(g_logger) << n;
    auto res = conn->recvResponse();
    if(!res) {
        SKYRPC_LOG_INFO(g_logger) << "recvResponse " << addr->toString() << " failed";
        return;
    }
    SKYRPC_LOG_INFO(g_logger) << res->toString();

}
void test_request() {
    skyrpc::http::HttpResult::ptr result = skyrpc::http::HttpConnection::DoGet("www.baidu.com");
                                //skyrpc::http::HttpConnection::DoGet("localhost:8080/index.html");
    SKYRPC_LOG_INFO(g_logger) << result->toString();
}
void test_pool(){
    skyrpc::http::HttpConnectionPool::ptr pool(new skyrpc::http::HttpConnectionPool(
            "www.baidu.com", "", 80, false, 10, 1000 * 30, 5));

    skyrpc::IOManager::GetThis()->addTimer(1000, [pool](){
        auto r = pool->doGet("/", -1, {{"connection", "keep-alive"}});
        SKYRPC_LOG_INFO(g_logger) << r->toString();

    }, true);
}
int main(){
    skyrpc::IOManager iom(2);
    iom.submit(test_request);
    //iom.submit(run);
    //iom.submit(test_pool);
    return 0;
}

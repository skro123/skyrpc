#include "skyrpc/skyrpc.h"

static auto g_logger = SKYRPC_LOG_ROOT();

void run() {
    auto addr = skyrpc::Address::LookupAny("0.0.0.0:8080");
    //auto addr = skyrpc::UnixAddress::ptr(new skyrpc::UnixAddress("/tmp/skyrpc/unix"));
    SKYRPC_LOG_DEBUG(g_logger) << addr->toString();

    skyrpc::TcpServer::ptr tcpServer(new skyrpc::TcpServer());

    while(!tcpServer->bind(addr)){
        sleep(3);
    }

    tcpServer->start();
    SKYRPC_LOG_DEBUG(g_logger) << "start";
    //sleep(10000);
}
int main(){
    go run;
}

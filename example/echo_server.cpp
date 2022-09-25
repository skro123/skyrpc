#include "skyrpc/byte_array.h"
#include "skyrpc/io_manager.h"
#include "skyrpc/log.h"
#include "skyrpc/net/tcp_server.h"

static skyrpc::Logger::ptr g_logger = SKYRPC_LOG_ROOT();

class EchoServer : public skyrpc::TcpServer {
public:
    void handleClient(skyrpc::Socket::ptr client) override {
        SKYRPC_LOG_INFO(g_logger) << "handleClient" << client->toString();
        skyrpc::ByteArray::ptr buff(new skyrpc::ByteArray);
        while (true) {
            buff->clear();
            std::vector<iovec> iovs;
            buff->getWriteBuffers(iovs, 1024);

            int n = client->recv(&iovs[0], iovs.size());
            //int n = 0;
            if(n == 0) {
                SKYRPC_LOG_INFO(g_logger) << "Client Close" << client->toString();
                break;
            } else if (n < 0){
                SKYRPC_LOG_INFO(g_logger) << "Client Error, errno=" << errno << " errstr=" << strerror(errno);
                break;
            }
            buff->setPosition(buff->getPosition() + n);
            buff->setPosition(0);
            SKYRPC_LOG_INFO(g_logger) << "Client: " << buff->toString();
            //client->send(buff);
        }
    }
};
void run(){
    EchoServer::ptr echoServer(new EchoServer);
    skyrpc::Address::ptr address = skyrpc::Address::LookupAny("127.0.0.1:8080");

    while(!echoServer->bind(address)) {
        sleep(2);
    }
    echoServer->start();
}
int main(){
    go run;
}
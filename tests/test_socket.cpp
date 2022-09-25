#include "skyrpc/log.h"
#include "skyrpc/io_manager.h"
#include "skyrpc/net/socket.h"
#include "skyrpc/net/socket_stream.h"
#include "skyrpc/byte_array.h"
static skyrpc::Logger::ptr g_logger = SKYRPC_LOG_ROOT();
void test_socket(){
    skyrpc::Address::ptr addr = skyrpc::IPAddress::Create("vvip.icu",80);
    if(addr){
        SKYRPC_LOG_DEBUG(g_logger) << addr->toString();
    } else {
        return;
    }
    skyrpc::Socket::ptr sock = skyrpc::Socket::CreateTCP(addr);
    if(sock->connect(addr)){
        SKYRPC_LOG_DEBUG(g_logger) << addr->toString() << " connected";
    } else {
        return;
    }
    char buff[]="GET / HTTP/1.0\r\n\r\n";
    sock->send(buff,sizeof buff);
    std::string str;
    str.resize(4096);
    sock->recv(&str[0],str.size());
    SKYRPC_LOG_INFO(g_logger)<<str;
}
std::set<skyrpc::Socket::ptr> clients;
void sendAll(skyrpc::Socket::ptr sock, const char *msg, int len){
    char* buff = new char[4096];
    sprintf(buff,"%d says: ",sock->getSocket());
    strcat(buff,msg);
    puts(buff);
    for(auto i : clients){
        if(i != sock){
            i->send(buff, strlen(buff));
        }
    }
    delete[] buff;
}
void test_server(){
    skyrpc::Address::ptr address = skyrpc::IPv4Address::Create("127.0.0.1", 8080);
    skyrpc::Socket::ptr sock = skyrpc::Socket::CreateTCPSocket();
    sock->bind(address);
    sock->listen();
    while(1){
        skyrpc::Socket::ptr client = sock->accept();
        clients.insert(client);
        sendAll(client,"New User, welcome him\n", 21);
        skyrpc::IOManager::GetThis()->submit([client]{
            char *buff = new char[4096];

            while(1){
                int n = client->recv(buff,4096);
                if(n == 0){
                    SKYRPC_LOG_INFO(g_logger) << "user quit";
                    break;
                }
                buff[n] = 0;
                //send(fd,buff,n,0);
                sendAll(client,buff,n);
            }
            sendAll(client,"user quit\n", 10);
            delete[] buff;
            clients.erase(client);
            client->close();
        });
    }
}
void test_byte_array() {
    skyrpc::Address::ptr addr = skyrpc::IPAddress::Create("localhost",8080);
    if(addr){
        SKYRPC_LOG_DEBUG(g_logger) << addr->toString();
    } else {
        return;
    }
    skyrpc::Socket::ptr sock = skyrpc::Socket::CreateTCP(addr);
    if(sock->connect(addr)){
        SKYRPC_LOG_DEBUG(g_logger) << addr->toString() << " connected";
    } else {
        return;
    }

    char buff[]="hello";
    skyrpc::ByteArray::ptr bt(new skyrpc::ByteArray());
    bt->write(buff, 6);
    bt->setPosition(0);
    //sock->send(buff,sizeof buff);

    skyrpc::SocketStream ss(sock);
    ss.writeFixSize(bt, 6);
    return;
    std::string str;
    str.resize(4096);
    sock->recv(&str[0],str.size());
    SKYRPC_LOG_INFO(g_logger)<<str;
}
int main(){
    skyrpc::IOManager ioManager{};
    ioManager.submit(&test_byte_array);
    //test_socket();
}
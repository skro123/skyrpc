#include <stdint.h>
#include <iostream>
#include "stdio.h"
#include <bit>
#include "skyrpc/net/address.h"
#include "skyrpc/log.h"
#include "skyrpc/io_manager.h"
#include "skyrpc/config.h"
static skyrpc::Logger::ptr g_logger = SKYRPC_LOG_ROOT();
char buff[100000];
void test_http(){
    skyrpc::Address::ptr address = skyrpc::IPAddress::Create("baidu.com", 80);
    //address->insert(std::cout);
    SKYRPC_LOG_INFO(g_logger) << address->toString();
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int rt = connect(fd, address->getAddr(), address->getAddrLen());
    SKYRPC_LOG_INFO(g_logger) << rt;
    //read(fd,buff,100);
    const char data[] = "GET / HTTP/1.0\r\n\r\n";
    rt = send(fd, data, sizeof(data), 0);
    char *p = buff;
    while((rt = recv(fd,p,4096,0)) > 0){
        p += rt;
    }

    puts(buff);
}
void test_addr(){
    std::vector<skyrpc::Address::ptr> res;
    skyrpc::Address::Lookup(res,"iptv.tsinghua.edu.cn");
    for(auto i:res){
        std::cout<<i->toString()<<std::endl;
    }
}
void test_iface(){
    std::multimap<std::string,std::pair<skyrpc::Address::ptr, uint32_t>> r;
    skyrpc::Address::GetInterfaceAddresses(r,AF_INET6);
    for(auto item:r){
        std::cout<<item.first<<','<<item.second.first->toString()<<','<<item.second.second<<'\n';
    }
}
void test_ipv4(){
    auto addr = skyrpc::IPAddress::Create("iptv.tsinghua.edu.cn");
    //auto addr = skyrpc::IPAddress::Create("127.0.0.8");
    if(addr) {
        SKYRPC_LOG_INFO(g_logger) << addr->toString();
    }
}
int main(){
    SKYRPC_LOG_INFO(g_logger) << "Main";
    //skyrpc::IOManager ioManager{};
    //ioManager.submit(&test_http);

    //test_addr();
    //test_iface();
    test_ipv4();
}
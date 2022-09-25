#include "skyrpc/log.h"
#include "skyrpc/net/uri.h"
using namespace skyrpc;
static Logger::ptr g_logger = SKYRPC_LOG_ROOT();


int main(){
    std::string http = "www.baidu.com/s?wd=%E4%BD%A0%E5%A5%BD";
    std::string https = "https://baidu.com/add?a=1&b=2#aaa";
    std::string ftp = "ftp://admin:passwd@www.myftp.com/profile";
    std::string file = "file:///c:/desktop/a.cpp";
    std::string magnet = "magnet:?xt=urn:btih:2F9D75F4CB3385CB06FFB30695A34FAC7033902C";
    SKYRPC_LOG_INFO(g_logger) << Uri::Create(http)->toString();
    SKYRPC_LOG_INFO(g_logger) << Uri::Create(https)->toString();
    SKYRPC_LOG_INFO(g_logger) << Uri::Create(ftp)->toString();
    SKYRPC_LOG_INFO(g_logger) << Uri::Create(file)->toString();
    SKYRPC_LOG_INFO(g_logger) << Uri::Create(magnet)->toString();
    SKYRPC_LOG_INFO(g_logger) << Uri::Create(https)->createAddress()->toString();
}
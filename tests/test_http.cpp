#include "skyrpc/http/http.h"
#include "skyrpc/log.h"
static skyrpc::Logger::ptr g_logger = SKYRPC_LOG_ROOT();
void test_request(){
    skyrpc::http::HttpRequest h;
    //h.setPath("/index.h");
    h.setHeader("host","vvip.icu");
    h.setBody("Hello, World");

    SKYRPC_LOG_INFO(g_logger) << '\n' << h.toString();
}
void test_response(){
    skyrpc::http::HttpResponse r;
    r.setHeader("host","vvip.icu");
    r.setBody("Hello, World");
    r.setStatus(404);
    SKYRPC_LOG_INFO(g_logger) << '\n' << r.toString();
}
int main(){

    test_response();
}
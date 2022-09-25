#include "skyrpc/skyrpc.h"
using namespace skyrpc;
static skyrpc::Logger::ptr g_logger = SKYRPC_LOG_ROOT();


void test_response_parse(){
    skyrpc::http::HttpResponseParser::ptr parser(new skyrpc::http::HttpResponseParser());
    char res[100] = "HTTP/1.0 404 NOT FOUND\r\nContent-Length: 23330\r\nDate: Thu,08 Mar 202107:17:51 GMT\r\n\r\n";
    parser->execute(res, strlen(res));
    SKYRPC_LOG_INFO(g_logger) << "\n" << parser->getData()->toString();

}
const char test_request_data[] = "POST / HTTP/1.1\r\n"
                                 "Host: www.skyrpc.icu\r\n"
                                 "Content-Length: 10\r\n\r\n";

void test_request() {
    skyrpc::http::HttpRequestParser parser;
    std::string tmp = test_request_data;
    size_t s = parser.execute(&tmp[0], tmp.size());
    SKYRPC_LOG_ERROR(g_logger) << "execute rt=" << s
                              << "has_error=" << parser.hasError()
                              << " is_finished=" << parser.isFinished()
                              << " total=" << tmp.size()
                              << " content_length=" << parser.getContentLength();
    tmp.resize(tmp.size() - s);
    SKYRPC_LOG_INFO(g_logger) << parser.getData()->toString();
    SKYRPC_LOG_INFO(g_logger) << tmp;
}

const char test_response_data[] = "HTTP/1.1 200 OK\r\n"
                                  "Date: Tue, 04 Jun 2050 15:43:56 GMT\r\n"
                                  "Server: Apache\r\n"
                                  "Last-Modified: Tue, 12 Jan 2010 13:48:00 GMT\r\n"
                                  "ETag: \"51-47cf7e6ee8400\"\r\n"
                                  "Accept-Ranges: bytes\r\n"
                                  "Content-Length: 81\r\n"
                                  "Cache-Control: max-age=86400\r\n"
                                  "Expires: Wed, 05 Jun 2019 15:43:56 GMT\r\n"
                                  "Connection: Close\r\n"
                                  "Content-Type: text/html\r\n\r\n"
                                  "<html>\r\n"
                                  "<meta http-equiv=\"refresh\" content=\"0;url=http://www.baidu.com/\">\r\n"
                                  "</html>\r\n";

void test_response() {
    skyrpc::http::HttpResponseParser parser;
    std::string tmp = test_response_data;
    size_t s = parser.execute(&tmp[0], tmp.size());
    SKYRPC_LOG_ERROR(g_logger) << "execute rt=" << s
                              << " has_error=" << parser.hasError()
                              << " is_finished=" << parser.isFinished()
                              << " total=" << tmp.size()
                              << " content_length=" << parser.getContentLength()
                              << " tmp[s]=" << tmp[s];

    tmp.resize(tmp.size() - s);

    SKYRPC_LOG_INFO(g_logger) << parser.getData()->toString() << tmp;
    //SKYRPC_LOG_INFO(g_logger) << tmp;
}
void test_vvip(){
    std::string str;
    str.resize(4096);
    skyrpc::http::HttpRequest request;
    request.setHeader("Host", "vvip.icu");
    auto sock = skyrpc::Socket::CreateTCPSocket();
    sock->connect(skyrpc::IPAddress::Create("vvip.icu",80));
    skyrpc::ByteArray buff;
    buff.writeStringWithoutLength(request.toString());
    //sock->send()
    buff.setPosition(0);
    //sock->send(buff);

    buff.clear();
    skyrpc::ByteArray buffer;
    //int n = sock->recv(buffer, 8000);
    int n = sock->recv(&str[0], 4096);
    SKYRPC_LOG_INFO(g_logger) << n;
    SKYRPC_LOG_INFO(g_logger) << str;
    n = sock->recv(&str[0], 4096);
    SKYRPC_LOG_INFO(g_logger) << n;
    SKYRPC_LOG_INFO(g_logger) << str;
    //str = buff.toString();
    //SKYRPC_LOG_INFO(g_logger) << buffer.toString();
//    skyrpc::http::HttpResponseParser response;
//    response.execute(&str[0],4096);
//    SKYRPC_LOG_INFO(g_logger) << response.getData()->toString() ;
//    SKYRPC_LOG_INFO(g_logger) << response.getContentLength();
//    SKYRPC_LOG_INFO(g_logger) << str.substr(0,response.getContentLength());
}
int main(){
    test_response();
    //IOManager ioManager{1};
    //ioManager.submit(&test_response);
    //ioManager.submit(&test_response_parse);
}
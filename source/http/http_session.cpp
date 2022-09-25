#include "skyrpc/http/http_session.h"
#include "skyrpc/http/parse.h"
#include "skyrpc/log.h"
namespace skyrpc::http {
static Logger::ptr g_logger = SKYRPC_LOG_NAME("system");
HttpSession::HttpSession(Socket::ptr socket, bool owner)
    : SocketStream(socket, owner) {
}

HttpRequest::ptr HttpSession::recvRequest() {
    HttpRequestParser::ptr parser(new HttpRequestParser);
    uint64_t buff_size = HttpRequestParser::GetHttpRequestBufferSize();
    std::string buffer;
    buffer.resize(buff_size);
    char* data = &buffer[0];
    size_t offset = 0;
    while (!parser->isFinished()) {
        ssize_t len = read(data + offset, buff_size - offset);
        if (len <= 0) {
            close();
            return nullptr;
        }
        len += offset;
        size_t nparse = parser->execute(data, len);
        if (parser->hasError() || nparse == 0) {
            SKYRPC_LOG_DEBUG(g_logger) << "parser error code:" << parser->hasError();
            close();
            return nullptr;
        }
        offset = len - nparse;
    }
    uint64_t length = parser->getContentLength();
    if (length >= 0) {
        std::string body;
        body.resize(length);
        size_t len = 0;
        if (length >= offset) {
            memcpy(&body[0], data, offset);
            len = offset;
        } else {
            memcpy(&body[0], data, length);
            len = length;
        }
        length -= len;
        if(length > 0) {
            if(readFixSize(&body[len], length) <= 0) {
                close();
                return nullptr;
            }
        }
        parser->getData()->setBody(body);
    }
    return parser->getData();
}

ssize_t HttpSession::sendResponse(HttpResponse::ptr response) {
    std::string str = response->toString();
    return writeFixSize(str.c_str(), str.size());
}

}
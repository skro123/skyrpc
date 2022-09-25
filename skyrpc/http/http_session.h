#ifndef SKYRPC_HTTP_SESSION_H
#define SKYRPC_HTTP_SESSION_H
#include <memory>
#include "skyrpc/net/socket_stream.h"
#include "http.h"

namespace skyrpc::http {
class HttpSession : public SocketStream {
public:
    using ptr = std::shared_ptr<HttpSession>;

    HttpSession(Socket::ptr socket, bool owner = true);

    HttpRequest::ptr recvRequest();

    ssize_t sendResponse(HttpResponse::ptr response);
};
}

#endif //SKYRPC_HTTP_SESSION_H

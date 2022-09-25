#ifndef SKYRPC_RPC_SESSION_H
#define SKYRPC_RPC_SESSION_H

#include "skyrpc/net/socket_stream.h"
#include "protocol.h"

namespace skyrpc::rpc {
/**
 * @brief rpc session 封装了协议的收发
 */
class RpcSession : public SocketStream {
public:
    using ptr = std::shared_ptr<RpcSession>;
    using MutexType = CoMutex;

    /**
     * @brief 构造函数
     * @param[in] sock Socket类型
     * @param[in] owner 是否托管Socket
     */
    RpcSession(Socket::ptr socket, bool owner = true);
    /**
     * @brief 接收协议
     * @return 如果返回空协议则接收失败
     */
    Protocol::ptr recvProtocol();
    /**
     * @brief 发送协议
     * @param[in] proto 要发送的协议
     * @return 发送大小
     */
    ssize_t sendProtocol(Protocol::ptr proto);
private:
    MutexType m_mutex;
};
}
#endif //SKYRPC_RPC_SESSION_H

#ifndef SKYRPC_FILE_SERVLET_H
#define SKYRPC_FILE_SERVLET_H
#include "../servlet.h"
namespace skyrpc::http {
class FileServlet : public Servlet {
public:
    using ptr = std::shared_ptr<FileServlet>;
    FileServlet(const std::string &path);
    int32_t handle(HttpRequest::ptr request, HttpResponse::ptr response, HttpSession::ptr session) override;
private:
    std::string m_path;
};

}
#endif //SKYRPC_FILE_SERVLET_H

#include "skyrpc/skyrpc.h"
#include <iostream>
static skyrpc::Logger::ptr g_logger = SKYRPC_LOG_ROOT();

int main(){
    //SKYRPC_LOG_DEBUG(g_logger) << SKYRPC_LOG_NAME("system").get()->getLevel();
    //SKYRPC_LOG_NAME("system").get()->setLevel(skyrpc::LogLevel::FATAL);
    //skyrpc::Config::LoadFromFile("../config/log.yaml");
    skyrpc::IOManager::ptr ioManager(new skyrpc::IOManager{4});
    ioManager->submit([]{
        skyrpc::Address::ptr address = skyrpc::Address::LookupAny("0.0.0.0:8081");
        skyrpc::http::HttpServer::ptr server(new skyrpc::http::HttpServer(true));
        server->getServletDispatch()->addGlobServlet("/*",
                     std::make_shared<skyrpc::http::FileServlet>("/mnt/c/Users/zavier/Desktop/skyrpc/static"));
        server->getServletDispatch()->addServlet("/a",[](skyrpc::http::HttpRequest::ptr request
                , skyrpc::http::HttpResponse::ptr response
                , skyrpc::http::HttpSession::ptr session) ->uint32_t {
            //std::string str = request->toString();
            response->setBody("hello world");
            //response->setBody(str + "<h1>hello world</h1>");
            //response->setContentType(skyrpc::http::HttpContentType::TEXT_HTML);
            return 0;
        });
        server->getServletDispatch()->addServlet("/add",[](skyrpc::http::HttpRequest::ptr request
                , skyrpc::http::HttpResponse::ptr response
                , skyrpc::http::HttpSession::ptr session) ->uint32_t {
            int a = request->getParamAs("a", 0ll);
            int b = request->getParamAs("b", 0ll);
            response->setBody(std::to_string(a) + " + " + std::to_string(b) + "=" + std::to_string(a+b));
            return 0;
        });

        server->getServletDispatch()->addServlet("/json",[](skyrpc::http::HttpRequest::ptr request
                , skyrpc::http::HttpResponse::ptr response
                , skyrpc::http::HttpSession::ptr session) ->uint32_t {
            skyrpc::Json json;
            switch (request->getMethod()) {
                case skyrpc::http::HttpMethod::GET:
                    json["bool"] = true;
                    json["number"] = 114514;
                    json["float"] = M_PI;
                    json["string"] = "abcdefg";
                    response->setJson(json);
                    break;
                case skyrpc::http::HttpMethod::POST:
                    json = request->getJson();
                    SKYRPC_LOG_INFO(g_logger) << json.type_name() << "\n" << json;
                    response->setJson(json);
                    break;
                default:
                    break;
            }
            return 0;
        });

        while (!server->bind(address)){
            sleep(1);
        }

        server->start();
    });
}
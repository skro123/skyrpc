#include "iostream"
#include "skyrpc/log.h"
#include "yaml-cpp/yaml.h"
#include "skyrpc/config.h"
auto port = skyrpc::Config::Lookup("system.port",8080,"bind port");

int main(){
    skyrpc::Config::LoadFromFile("config/log.yaml");

    SKYRPC_LOG_ROOT()->setFormatter("%n -- %m --%n ");
    //std::cout << skyrpc::LogMgr::GetInstance()->toString()<<std::endl;
    SKYRPC_LOG_ERROR(SKYRPC_LOG_ROOT())<<"aaa";
}
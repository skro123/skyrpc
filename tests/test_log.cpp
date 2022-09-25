#include "skyrpc/log.h"
#include "skyrpc/util.h"
#include <iostream>
#include <memory>
using namespace std;
int main(){
    //source::Logger::ptr logger(std::make_shared<source::Logger>());
    auto logger = skyrpc::LogMgr::GetInstance()->getLogger("system");
    SKYRPC_LOG_ERROR(logger)<<"system";
  //cout<<"hello";
}

#include "skyrpc/fiber.h"
#include "skyrpc/log.h"

skyrpc::Logger::ptr g_logger = SKYRPC_LOG_ROOT();
int count = 0;
void run_in_fiber(){
    SKYRPC_LOG_INFO(g_logger)<<"run_in_fiber begin";
    skyrpc::Fiber::YieldToReady();
    SKYRPC_LOG_INFO(g_logger)<<"run_in_fiber end";
}

void test1(){
    //skyrpc::Fiber::EnableFiber();
    SKYRPC_LOG_INFO(g_logger)<<"begin";
    skyrpc::Fiber::ptr fiber(new skyrpc::Fiber(run_in_fiber));
    fiber->resume();
    SKYRPC_LOG_INFO(g_logger)<<"after swap in";
    fiber->resume();
    SKYRPC_LOG_INFO(g_logger)<<"end";
}
void test2(){
    skyrpc::Fiber::ptr fiber(new skyrpc::Fiber([](){
        while (1){
            count++;
            skyrpc::Fiber::YieldToReady();
        }
    }));
    while (1){
        fiber->resume();
        SKYRPC_LOG_DEBUG(g_logger)<<count;
    }

}

int main(int argc, char **argv){
    skyrpc::Fiber::EnableFiber();
    // go test1;
}
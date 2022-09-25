#include <unistd.h>
#include "skyrpc/skyrpc.h"
static skyrpc::Logger::ptr g_logger = SKYRPC_LOG_ROOT();

void test_fiber() {
    static int s_count = 5;
    SKYRPC_LOG_INFO(g_logger) << "test in fiber s_count=" << s_count;

    sleep(1);
    while(--s_count >= 0) {
        //skyrpc::Fiber::GetThis()->YieldToReady();

        //skyrpc::Fiber::GetThis()->YieldToReady();
        //skyrpc::Scheduler::GetThis()->submit(&test_fiber, skyrpc::GetThreadId());
        skyrpc::Fiber::YieldToReady();
        SKYRPC_LOG_INFO(g_logger) << "resum  " << s_count;
    }
    SKYRPC_LOG_INFO(g_logger) << "test end" << s_count;
}

void test_fiber2(){
    while(1){
        SKYRPC_LOG_INFO(g_logger) << "while " ;
        sleep(2);
        skyrpc::Fiber::YieldToReady();
    }
}

void test3(){
    SKYRPC_LOG_INFO(g_logger) << "main";
    skyrpc::Scheduler sc(3,"test");
    sc.start();
    sleep(2);
    SKYRPC_LOG_INFO(g_logger) << "schedule";
    sc.submit(&test_fiber);
    //sc.submit(skyrpc::Fiber::ptr (new skyrpc::Fiber(&test_fiber)));
    //sc.submit(&test_fiber2);
    //sleep(8);
    //sc.stop();
    while(1);
    SKYRPC_LOG_INFO(g_logger) << "over";
}

int main(int argc, char** argv) {
    SKYRPC_LOG_DEBUG(g_logger) << "main";
    skyrpc::Scheduler sc(3,"test");
    sc.start();
    sc.submit([]{
        SKYRPC_LOG_INFO(g_logger) << "hello world";
    });
    return 0;
}
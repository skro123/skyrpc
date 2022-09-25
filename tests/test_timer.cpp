#include "skyrpc/skyrpc.h"
#include <iostream>
#include "sys/time.h"
static skyrpc::Logger::ptr g_logger = SKYRPC_LOG_ROOT();
void test5(){
    skyrpc::IOManager ioManager{3};

    skyrpc::Timer::ptr timer1 = ioManager.addTimer(5000,[&timer1]{
        static int i =0;
        i++;
        if(i==3){
            //timer1->reset(2000, true);
            //timer1->refresh();
        }
        SKYRPC_LOG_INFO(g_logger) << i <<" seconds 3";
    }, true);
    skyrpc::Timer::ptr timer = ioManager.addTimer(2000,[&timer,&timer1]{
        static int i =0;
        i++;
        if(i==3){
            //timer->reset(1000, true);
            //timer->cancel();
            //timer1->refresh();
        }
        SKYRPC_LOG_INFO(g_logger) << i <<" seconds 2";
    }, true);
    ioManager.start();
    //sleep(100);

}
skyrpc::Timer::ptr s_timer;
void test1(){
    skyrpc::IOManager ioManager{};
    s_timer = ioManager.addTimer(2,[]{
        static int i =0;
        i++;
        if(i%1000==0){
            //s_timer->reset(1,false);
            s_timer->cancel();
            //t->refresh();
            SKYRPC_LOG_INFO(g_logger) << i <<" seconds";
        }
    }, true);
}
int main(){
    test1();
}
#include "skyrpc/skyrpc.h"
#include <memory>
#include <cstdlib>
int n=0;
skyrpc::RWMutex rwmutex;
skyrpc::Mutex mutex;
void f(){
    SKYRPC_LOG_WARN(SKYRPC_LOG_NAME("system"))
        <<"skyrpc::Thread::GetName()  "<<skyrpc::Thread::GetName()
        <<"skyrpc::Thread::GetThis()->getName()  "<<skyrpc::Thread::GetThis()->getName()
        <<"skyrpc::Thread::GetThis()->getId(); " <<skyrpc::Thread::GetThis()->getId()
        <<"skyrpc::GetThreadId() "<<skyrpc::GetThreadId();
    //skyrpc::ScopedLock<skyrpc::Mutex> a(mutex);
    //skyrpc::RWMutex::ReadLock a(rwmutex);
    //skyrpc::RWMutex::WriteLock a(rwmutex);
    for(int i=0;i<10000000;i++){
        //skyrpc::ScopedLock<skyrpc::Mutex> a(mutex);
        //skyrpc::RWMutex::ReadLock a(rwmutex);
        //skyrpc::RWMutex::WriteLock a(rwmutex);
        n++;
    }
}
void f2(){
    //skyrpc::Thread t;
    skyrpc::TimeMeasure time;
    skyrpc::Thread::ptr thread[10];

    for(int i=0;i<10;i++){
        thread[i]=std::make_shared<skyrpc::Thread>(std::to_string(i)+" t",&f);
    }

    for(int i=0;i<10;i++){
        thread[i]->join();
    }
    std::cout<<n;
}
void p1(){
    for (int i = 0; ; ++i) {
        SKYRPC_LOG_WARN(SKYRPC_LOG_ROOT())<<"++++++++++++++++++++++++++";
    }

};
void p2(){
    for (int i = 0; ; ++i) {
        SKYRPC_LOG_ERROR(SKYRPC_LOG_ROOT())<<"-----------------------------";
    }

};
int main(){
    skyrpc::Thread b("f1",&p1);
    skyrpc::Thread a("f2",&p2);
    a.join();
    b.join();
}
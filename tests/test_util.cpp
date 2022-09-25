#include "skyrpc/skyrpc.h"
#include <vector>
#include <iostream>
void test( int n){
    //constexpr int c=0;
    SKYRPC_ASSERT2(0,"Not zero");
    //SKYRPC_STATIC_ASSERT(c);
    //skyrpc::Assert(0,"Void test(int)");
}
void test_defer() {
    Defer_ {
        LOG_DEBUG << "no log";
    };
    Defer {
          LOG_DEBUG << "defer c";
          LOG_DEBUG << "defer d";
    };
    defer []{
        LOG_DEBUG << "defer a";
    };
    defer []{
        LOG_DEBUG << "defer b";
    };
}
int main(){
    test_defer();
}
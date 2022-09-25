#include "skyrpc/rpc/serializer.h"
#include "skyrpc/rpc/rpc.h"
#include "skyrpc/log.h"
#include "skyrpc/config.h"
#include <iostream>
static skyrpc::Logger::ptr g_logger = SKYRPC_LOG_ROOT();
void test1() {
    skyrpc::rpc::Serializer s;
    skyrpc::rpc::Result<int> r, t;
    r.setCode(skyrpc::rpc::RPC_SUCCESS);
    r.setVal(23);
    s << r;
    s.reset();
    s >> t;
    SKYRPC_LOG_DEBUG(g_logger) << t.toString();
}
void test2() {
    std::list<std::string> a;
    a.push_back("aa");
    a.push_back("bb");
    skyrpc::rpc::Serializer s;
    s << a;
    s.reset();
    std::list<std::string> b;
    s >> b;
    SKYRPC_LOG_DEBUG(g_logger) << std::endl << skyrpc::LaxicalCast<std::list<std::string>,std::string>()(b);
}
void test3() {
    std::vector<std::string> a;
    a.push_back("aa");
    a.push_back("bb");
    skyrpc::rpc::Serializer s;
    s << a;
    s.reset();
    std::vector<std::string> b;
    s >> b;
    SKYRPC_LOG_DEBUG(g_logger) << std::endl << skyrpc::LaxicalCast<std::vector<std::string>,std::string>()(b);
}

void test4() {
    std::set<std::string> a {"aa","bb"};
    skyrpc::rpc::Serializer s;
    s << a;
    s.reset();
    std::set<std::string> b;
    s >> b;
    SKYRPC_LOG_DEBUG(g_logger) << std::endl << skyrpc::LaxicalCast<std::set<std::string>,std::string>()(b);
}

void test5() {
    std::map<int,std::vector<std::string>> a {{5,{"aa","bb"}},{7,{"aac","bbc"}}};
    skyrpc::rpc::Serializer s;
    s << a;
    s.reset();
    std::map<int,std::vector<std::string>> b;
    s >> b;
    for(auto item:b){
        SKYRPC_LOG_INFO(g_logger) << item.first << " " << item.second.size();//<< item.second;
        for(auto i:item.second) {
            SKYRPC_LOG_INFO(g_logger) << i << " " ;
        }
    }
}

template<typename T>
void test_map(T& a) {
    skyrpc::rpc::Serializer s;
    s << a;
    s.reset();
    T b;
    s >> b;
    for(auto item:b){
        SKYRPC_LOG_INFO(g_logger) << item.first << " " << item.second;//<< item.second;
    }
}

void test6() {
    std::map<int, std::string> a{{1,"a"},{2,"b"}};
    test_map(a);
}

void test7() {
    std::multimap<int, std::string> a{{1,"a"},{1,"a"}};
    test_map(a);
}

void test8() {
    std::unordered_multimap<int, std::string> a{{1,"a"},{1,"a"}};
    test_map(a);
}

void test9() {
    std::unordered_map<int, std::string> a{{1,"a"},{1,"a"}};
    test_map(a);
}

void seq2seq() {
    std::vector<std::string> a{"ab","cd"};
    skyrpc::rpc::Serializer s;
    s << a;
    std::list<std::string> b;
    s.reset();
    s >> b;
    SKYRPC_LOG_DEBUG(g_logger) << std::endl << skyrpc::LaxicalCast<std::list<std::string>,std::string>()(b);
}

void map2map() {

}

int main() {
    test6();
}
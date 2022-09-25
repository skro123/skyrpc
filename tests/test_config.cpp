#include <list>
#include "skyrpc/log.h"
#include "skyrpc/config.h"
#include "yaml-cpp/yaml.h"
using namespace std;
auto port = skyrpc::Config::Lookup("system.port",8080,"bind port");
auto vec = skyrpc::Config::Lookup("system.vec",vector<int>{2,3},"vec");
//auto logss = skyrpc::Config::Lockup("logs",vector<string>(),"logs");
class Person{
public:
    Person() = default;
    Person(const string& name,int age): m_age(age), m_name(name){}
    int m_age = 0;
    std::string m_name ;
    std::string toString() const {
        std::stringstream ss;
        ss<<"[ name="<<m_name<<", age="<<m_age<<" ]";
        return ss.str();
    }
    bool operator==(const Person& oth){
        return m_age == oth.m_age && m_name == oth.m_name;
    }
};
namespace skyrpc{
template<>
class LaxicalCast<std::string ,Person>{
public:
    Person operator()(const std::string& str){
        YAML::Node node = YAML::Load(str);
        Person res;
        res.m_name = node["name"].as<std::string>();
        res.m_age = node["age"].as<int>();
        return res;
    }
};

template<>
class LaxicalCast<Person ,std::string >{
public:
    std::string operator()(const Person& v){
        YAML::Node node;
        node["name"] = v.m_name;
        node["age"] = v.m_age;
        std::stringstream ss;
        ss<<node;
        return ss.str();
    }
};
}
void test1(){
    SKYRPC_LOG_DEBUG(SKYRPC_LOG_ROOT())<<"Before \n"<<vec->toString();

    //YAML::Node config = YAML::LoadFile("config/log.yaml");
    skyrpc::Config::LoadFromFile("config/log.yaml");
    skyrpc::Config::Lookup("system.port","123"s,"vec");
    SKYRPC_LOG_DEBUG(SKYRPC_LOG_ROOT())<<"After \n"<<vec->toString();
    //cout<<skyrpc::LaxicalCast<string,vector<int>>()("- 1\n- 2\n- 5")[2];
    //cout<<skyrpc::LaxicalCast<list<list<vector<int>>>,string>()(list<list<vector<int>>>{{{1,2,4,5},{2,3}}});
    list<float> value{1.2,3.1415};
    cout<<skyrpc::LaxicalCast<map<string,list<float>>,string>()(map<string,list<float>> {{"skyrpc",value}});
}
void test2(){
    //auto pm = skyrpc::Config::Lookup("map",map<string,vector<Person>>(),"");

    //pm->setValue(map<string,vector<Person>>());
    auto a = skyrpc::Config::Lookup("class.person",Person(),"");
//    a->addListener(1,[](const auto& old_val, const auto& new_val){
//        SKYRPC_LOG_INFO(SKYRPC_LOG_ROOT())<<old_val.toString()<<" -> "<<new_val.toString();
//    });

    a->setValue(Person("aaa",44));
    //SKYRPC_LOG_DEBUG(SKYRPC_LOG_ROOT())<<"Before \n"<<a->toString()<<" "<<a->getValue().toString();
    //skyrpc::Config::LoadFromFile("config/log.yaml");
    SKYRPC_LOG_ERROR(SKYRPC_LOG_ROOT())<<"After \n"<<a->toString()<<" "<<a->getValue().toString();;
    //auto tmp = pm->getValue();
    skyrpc::Config::Visit([](skyrpc::ConfigVarBase::ptr config){
        SKYRPC_LOG_WARN(SKYRPC_LOG_ROOT())<<config->getName()<<" "<<config->getDescription()<<" "<<config->toString();
    });

    //auto b = a->getValue().toString();
}
int main(){
    test2();
    //std::cout<<skyrpc::LogMgr().GetInstance()->toYaml();
}

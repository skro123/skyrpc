#ifndef SKYRPC_SINGLETON_H
#define SKYRPC_SINGLETON_H

#include <memory>
#include "thread.h"
namespace skyrpc{
template<typename T>
class Singleton{
public:
    static T* GetInstance(){
        static T instance;
        return &instance;
    }

};

template<typename T>
class SingletonPtr{
public:
    static std::shared_ptr<T> GetInstance(){
        static std::shared_ptr<T> instance(std::make_shared<T>());
        return instance;
    }
};

}
#endif //SKYRPC_SINGLETON_H

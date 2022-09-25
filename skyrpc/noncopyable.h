#ifndef SKYRPC_NONCOPYABLE_H
#define SKYRPC_NONCOPYABLE_H

class Noncopyable{
public:
    Noncopyable() = default;
    ~Noncopyable() = default;
    Noncopyable(const Noncopyable& noncopyable) = delete;
    Noncopyable& operator=(const Noncopyable& noncopyable) = delete;
};
#endif //SKYRPC_NONCOPYABLE_H

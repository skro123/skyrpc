#include "skyrpc/io_manager.h"
#include "skyrpc/log.h"
#include "skyrpc/sync.h"
#include "skyrpc/time_measure.h"
using namespace skyrpc;
// 测试协程同步原语
static Logger::ptr g_logger = SKYRPC_LOG_ROOT();

using MutexType = CoMutex;
MutexType mutexType;
CoCondVar condVar;
volatile int n = 0;
void a() {
    TimeMeasure timeMesure;
    for (int i = 0; i < 100000; ++i) {
        MutexType::Lock lock(mutexType);
        ++n;
        //SKYRPC_LOG_INFO(g_logger) << n;
    }
    SKYRPC_LOG_INFO(g_logger) << n;
}

void b() {
    for (int i = 0; i < 100000; ++i) {
        MutexType::Lock lock(mutexType);
        ++n;
        //SKYRPC_LOG_INFO(g_logger) << n;
    }
    SKYRPC_LOG_INFO(g_logger) << n;
}

void test_mutex() {
    IOManager loop{};
    loop.submit(a);//->submit(b);
    loop.submit(b);
}

void cond_a() {
    MutexType::Lock lock(mutexType);
    SKYRPC_LOG_INFO(g_logger) << "cond a wait";
    condVar.wait(lock);
    SKYRPC_LOG_INFO(g_logger) << "cond a notify";
}
void cond_b() {
    MutexType::Lock lock(mutexType);
    SKYRPC_LOG_INFO(g_logger) << "cond b wait";
    condVar.wait(lock);
    SKYRPC_LOG_INFO(g_logger) << "cond b notify";
}
void cond_c() {
    sleep(2);
    SKYRPC_LOG_INFO(g_logger) << "notify cone";
    condVar.notify();
    sleep(2);
    SKYRPC_LOG_INFO(g_logger) << "notify cone";
    condVar.notify();
}
void test_condvar() {
    IOManager loop{};
    loop.submit(cond_a);//->submit(b);
    loop.submit(cond_b);
    loop.submit(cond_c);
}
CoSemaphore sem(5);
void sem_a() {
    for (int i = 0; i < 5; ++i) {
        sem.wait();
    }
    SKYRPC_LOG_INFO(g_logger) << "sem_a sleep 2s";
    sleep(2);
    for (int i = 0; i < 5; ++i) {
        sem.notify();
    }
}
void sem_b() {
    SKYRPC_LOG_INFO(g_logger) << "sem_b sleep 1s";
    sleep(1);
    for (int i = 0; i < 5; ++i) {
        sem.wait();
    }
    SKYRPC_LOG_INFO(g_logger) << "sem_b notify";
    for (int i = 0; i < 5; ++i) {
        sem.notify();
    }
}
void test_sem() {
    IOManager loop{};
    loop.submit(sem_a);//->submit(b);
    loop.submit(sem_b);
}

void chan_a(Channel<int> chan) {
    for (int i = 0; i < 10; ++i) {
        chan << i;
        SKYRPC_LOG_INFO(g_logger) << "provider " << i;
    }
    SKYRPC_LOG_INFO(g_logger) << "close";
    chan.close();
}

void chan_b(Channel<int> chan) {
    int i = 0;
    while (chan >> i) {
        SKYRPC_LOG_INFO(g_logger) << "consumer " << i;
    }
    SKYRPC_LOG_INFO(g_logger) << "close";
}
void test_channel() {
    IOManager loop{};
    Channel<int> chan(5);
    loop.submit(std::bind(chan_a, chan));
    loop.submit(std::bind(chan_b, chan));
}
void test_countdown() {
    Go {
        CoCountDownLatch cnt(5);
        for (int i = 0; i < 5; ++i) {
            go [i, &cnt] {
                sleep(i);
                LOG_DEBUG << cnt.getCount();
                cnt.countDown();
            };
        }
        go[&cnt] {
            cnt.wait();
            LOG_DEBUG << cnt.getCount();
        };
        go[&cnt] {
            cnt.wait();
            LOG_DEBUG << cnt.getCount();
        };
        cnt.wait();
        LOG_DEBUG << cnt.getCount();
    };
}
int main() {
    //test_mutex();
    //est_condvar();
    //test_sem();
    //test_channel();
    test_countdown();
}
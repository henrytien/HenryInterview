#ifndef _THREAD_BASE_H_
#define _THREAD_BASE_H_
#include<pthread.h>
#include<iostream>
#include<unistd.h>
class ThreadBase {
public:
    ThreadBase();
    virtual ~ThreadBase();
    void start();
    void join();
private:
    // 为了派生类定义自己的实体
    virtual void run() = 0;
    static void* thread_routine(void* arg);
    pthread_t threadId_;
};

#endif // _THREAD_BASE_H_
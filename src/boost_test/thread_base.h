#ifndef _THREAD_BASE_H_
#define _THREAD_BASE_H_
#include<pthread.h>
#include<iostream>
#include<unistd.h>
#include<functional>
using namespace std;
class ThreadBase {
public:
    typedef std::function<void()> thread_func;
    explicit ThreadBase(const thread_func& func);
    void start();
    void join();
    void set_auto_delete(bool auto_delete);
private:
    
    void run();
    static void* thread_routine(void* arg);
    thread_func func_;
    pthread_t threadId_;
    bool auto_delete_;
};

#endif // _THREAD_BASE_H_
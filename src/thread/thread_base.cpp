#include"thread_base.h"


ThreadBase::ThreadBase(){
    std::cout << "Thread ...\n"; 
}
ThreadBase::~ThreadBase(){
    std::cout << "~Thread ...\n";
}
void ThreadBase::start() {
    // 线程启动的函数是什么呢？
    // 线程启动的参数怎么传递进去呢？
    pthread_create(&threadId_,NULL,thread_routine,this);
}
// 线程join()
void ThreadBase::join() {
    pthread_join(threadId_,NULL);
}

void* ThreadBase::thread_routine(void* arg) {
    // 这里可以直接调用run()方法么？
    // 这里要思考如何获取this指针
    // static_cast的作用在这里是将派生类指针转换为基类指针
    ThreadBase* t = static_cast<ThreadBase*>(arg);
    t->run();
    return NULL;
}
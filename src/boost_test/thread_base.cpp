#include"thread_base.h"

// 你知道怎么显示构造一个函数么
ThreadBase::ThreadBase(const thread_func &func):func_(func),auto_delete_(false){
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
    if (t->auto_delete_) {
        delete t;
    }
    return NULL;
}

void ThreadBase::set_auto_delete(bool auto_delete) {
    auto_delete_ = auto_delete;
}
// 这里是一个回调函数？
void ThreadBase::run() {
    func_();
}
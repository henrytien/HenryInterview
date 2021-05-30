#include"thread_base.h"
/*
// TestThread 继承Thread
class TestThread : public ThreadBase {
public:
    TestThread(int count) :count_(count) {
        std::cout << "TestThread ...\n";
    }
    ~TestThread() {
        std::cout << "~TestThread ...\n";
    }
private:
    // 请思考为什么这里访问属性设为private
    void run() {
        while (count_--) {
            std::cout << "this is a test ...\n";
            sleep(1);
        }
    }
private:
    int count_;
};
*/

// 普通的全局函数也是支持的
void thread_func() {
    cout << "thread_func ..." << endl;
}

void thread_func2(int count) {
    while (count--) {
        cout << "thread_func2 ..." << endl;
        sleep(1);
    }
}
int main() {
    ThreadBase t1(thread_func);
    ThreadBase t2(std::bind(thread_func2,3));
    t1.start();
    t2.start();
    t1.join();
    t2.join();
    return 0;
}
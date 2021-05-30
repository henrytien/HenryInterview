#include"thread_base.h"

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
int main() {
    /*
    TestThread t(5);
    t.start();
    t.join();
    */
   TestThread* t1 = new TestThread(5);
   t1->set_auto_delete(true);
   t1->start();
   t1->join();

    // 请思考上面的对象还能自动销毁么？
    // 如果要做到自动销毁该怎么处理？
   for(;;)
    pause();
    return 0;
}
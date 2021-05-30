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

    TestThread t(5);
    t.start();
    t.join();
    return 0;
}
#include"thread_base.h"


class Foo {
public:
    Foo(int count) :count_(count) {
    }
    ~Foo() {
    }

    void member_func() {
        while (count_--) {
            std::cout << "this is a test ...\n";
            sleep(1);
        }
    }

    void member_func2(int x) {
        while (count_--) {
            std::cout << "member_func2 " << x << " this is a test ...\n";
            sleep(1);
        }
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
    Foo foo(3);
    // 你知道这里为什么要取地址么？
    ThreadBase t3(std::bind(&Foo::member_func,foo));
    Foo foo2(3);
    ThreadBase t4(std::bind(&Foo::member_func2,foo2,1000));
    
    t1.start();
    t2.start();
    t3.start();
    t4.start();

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}
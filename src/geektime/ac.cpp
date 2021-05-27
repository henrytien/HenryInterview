#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <utility>
#include <functional>
using namespace std;
class scoped_thread {
public:
    template<typename ... Arg>
    scoped_thread(Arg&& ...arg)
    :thread_(std::forward<Arg>(arg)...){}
    scoped_thread(const scoped_thread&) = delete;
    ~scoped_thread() {
        if (thread_.joinable()) {
            thread_.join();
        }
    }
private:
    thread thread_;
};

mutex output_lock;

void func(const char* name) {
    this_thread::sleep_for(100ms);
    lock_guard<mutex> guard{output_lock};
    cout << "I am thead " << name << endl;
}

void work(condition_variable& cv, int& result) {
    this_thread::sleep_for(2s);
    result = 42;
    cv.notify_one();
}
bool ready = false;

int main() {
    // scoped_thread t1{func,"Henry"};
    // scoped_thread t2{func, "Tien"};

    condition_variable cv;
    mutex mut_cv;
    int result = 520;
    scoped_thread th{work,ref(cv),ref(result)};
    
    cout << "I am waiting now\n" << endl;
    unique_lock<std::mutex> lk(mut_cv);
    cv.wait(lk,[]{return ready;});

    cout << "Answer: " << result << endl;
    return 0;
}
#include<chrono>
#include<thread>
#include<iostream>
#include<future>

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

void work(promise<string> prom) {
    this_thread::sleep_for(2s);
    prom.set_value("I love wxy");
}
int main() {
    promise<string> prom;
    auto fut = prom.get_future();
    scoped_thread{work, move(prom)};
    promise<void> promv;
    // scoped_thread{work, move(promv)};

    cout << "I'am waitting for you\n";
    cout << "Answer: " << fut.get() << endl;
    return 0;
}
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
void workp(promise<string> prom) {
    this_thread::sleep_for(2s);
    prom.set_value("I love wxy");
}
string work() {
    this_thread::sleep_for(2s);
    return "I love wxy";
}
int main() {
    // promise<string> prom;
    // auto fut1 = prom.get_future();
    // prom.set_value("I love wxy");
    // scoped_thread{workp, move(prom)};

    packaged_task<string()> task{work};
    auto fut = task.get_future();
    cout << "Answer: " << fut.get() << endl;

    scoped_thread th{move(task)};
    this_thread::sleep_for(1s);
    cout << "I'am waitting for you\n";
    cout << "Answer: " << fut.get() << endl;
    return 0;
}
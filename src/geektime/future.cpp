#include <chrono>
#include <future>
#include <iostream>
#include <thread>

using namespace std;

string work() {
    this_thread::sleep_for(2s);
    return "I love you too!";
}

int main() {
    auto fut = async(launch::async, work);
    cout << "I'am waitting now\n";
    cout << "Answer: " << fut.get() << endl;
    cout << "Answer: " << fut.get() << endl;
    return 0;
}

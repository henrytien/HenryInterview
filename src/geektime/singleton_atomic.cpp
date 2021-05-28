#include<atomic>
#include<mutex>

using namespace std;

class Singleton {
public:
    static Singleton* instance();
private:
    // Singleton() {}
    // ~Singleton(){}
    // Singleton(const Singleton& signal);
    // Singleton& operator= (const Singleton& signal);
    static atomic<Singleton*> ins_ptr_;
    static mutex lock_;
};

atomic<Singleton*> Singleton::ins_ptr_;
std::mutex Singleton::lock_;

Singleton* Singleton::instance() {
    Singleton* ptr = Singleton::ins_ptr_.load(memory_order_acquire);
    if (ptr == nullptr) {
        lock_guard<mutex> {Singleton::lock_};
        ptr = Singleton::ins_ptr_.load(memory_order_relaxed);
        if (ptr == nullptr) {
            ptr = new Singleton();
            Singleton::ins_ptr_.store(ptr, memory_order_release);
        }
    }
    return Singleton::ins_ptr_;
}

int main() {
    Singleton* ptr = Singleton::instance();
    return 0;
}
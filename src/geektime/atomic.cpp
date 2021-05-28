#include<atomic>
#include<iostream>
using namespace std;

atomic_long count_;
void add_count() noexcept {
    count_.fetch_add(1, std::memory_order_relaxed);
}

int main() {
    atomic<int> y;
    int x =1;
    y.store(2,memory_order_release);

    if (y.load(memory_order_acquire) == 2) {
        x = 3;
        y.store(4,memory_order_relaxed);
    }

    add_count();
    return 0;
}




[shared_from_this](https://en.cppreference.com/w/cpp/memory/enable_shared_from_this/shared_from_this)

**Notes**
> It is permitted to call shared_from_this only on a previously shared object.
```cpp
#include <iostream>
#include <memory>
 
struct Foo : public std::enable_shared_from_this<Foo> {
    Foo() { std::cout << "Foo::Foo\n"; }
    ~Foo() { std::cout << "Foo::~Foo\n"; } 
    std::shared_ptr<Foo> getFoo() { return shared_from_this(); }
    std::shared_ptr<Foo> pf3;
    std::shared_ptr<Foo> getHenry() {
        std::cout << "pf3: " << pf3 << std::endl;
        return pf3;}
};
 
int main() {
    Foo *f = new Foo;
    std::shared_ptr<Foo> pf1;
 
    {
        std::shared_ptr<Foo> pf2(f); // hennry
        // pf1 = pf2->getFoo();  // shares ownership of object with pf2
        pf1 = pf2->getFoo(); // shares ownership of object with pf2
        pf1 = pf2->getHenry();
    }
 
    std::cout << "pf2 is gone\n";   
}


```
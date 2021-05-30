#include<iostream>
// #include<boost/function.hpp>
// #include<boost/bind.hpp>
#include<functional>
using namespace std;
using namespace std::placeholders;
class Foo {
public:
    void member_func(double d, int i, int j) {
        cout << d << endl; 
        cout << i << endl;
        cout << j << endl;
    }
};

int main() {
    Foo foo;
    // 你知道bind的参数含义么？
    // 第一个成员函数适配成新的函数类型
    // 第二个是隐式的成员函数的第一个参数this指针 Foo*
    // boost::function<void(int)> fp = boost::bind(&Foo::member_func,&foo,0.5,_1,10);
    std::function<void(int)> fp = std::bind(&Foo::member_func,&foo,0.5,_1,10);
    fp(100);
    return 0;
}

/*
0.5
100
10
*/

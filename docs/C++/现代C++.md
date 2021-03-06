## **01 |** 堆、栈、RAII : C++ 里该如何管理资源?

1. **RAII**是什么呢？
2. 栈的增长方向是？

## 02 | **自己动手，实现** C++ 的智能指针

1. 请看下面这段代码和智能指针有什么缺别？

   ```c++
   template <typename T>
   class smart_ptr {
   public:
       explicit smart_ptr(T *ptr = nullptr)
           : ptr_(ptr) {}
       ~smart_ptr()
       {
           delete ptr_;
       }
   
       // smart_ptr(const smart_ptr&) = delete;
       // smart_ptr& operator=(const smart_ptr&) = delete;
       smart_ptr(smart_ptr &&other)
       {
           ptr_ = other.release();
       }
       smart_ptr &operator=(smart_ptr rhs)
       {
           rhs.swap(*this);
           return *this;
       }
   
       T &operator*() const { return *ptr_; }
       T *operator->() const { return ptr_; }
       operator bool() const { return ptr_; }
       T *get() const { return ptr_; }
   
   private:
       T *ptr_;
   };
   
   int main() {
       smart_ptr<shape> ptr1{create_shape(shape_type::cycle)};
       smart_ptr<shape> ptr2{ptr1}; //编译错误
       smart_ptr<shape> ptr3;
   
       ptr3 = ptr1;                            // 编译错误
       ptr3 = std::move(ptr1);                 // ok
       smart_ptr<shape> ptr4{std::move(ptr3)}; // ok
                                               // 这里你看出这个类似哪个智能指针的行为了呢？
   }
   ```

2. 你可以实现一个子类指针向基类指针转换么？

   ```c++
   template <typename U>
   smart_ptr(smart_ptr<U> &&other)
   {
       ptr_ = other.release();
   }
   ```

3. 你能接着实现一个引用计数接口么？

   ```c++
   class shared_count {
   public:
       shared_count();
       void add_count();
       long reduce_count();
       long get_count() const();
   };
   ```

4. 现在需要你实现非线程安全的引用计数接口？

   ```c++
   class shared_count {
   public:
       shared_count() : count_(1) {}
       void add_count()
       {
           ++count_;
       }
   
       long reduce_count()
       {
           --count_;
       }
   
       long get_count() const
       {
           return count_;
       }
   
   private:
       long count_;
   };
   ```

5. 现在你需要把之前的构造函数和析构函数进行修改，可以支持引用计数能实现么？

   ```c++
   template <typename T>
   class smart_ptr {
   public:
       explicit smart_ptr(T* ptr = nullptr)
       :ptr_(ptr) {
           if (ptr) {
               shared_count_ = new shared_count();
           }
       }
       ~smart_ptr() {
           if (ptr_ && !shared_count_->reduce_count())
           {
               delete ptr_;
               delete shared_count_;
           }
       }
   private:
       T* ptr_;
       shared_count* shared_count_;
   };
   ```

6. 你可以添加一个swap函数么？

   ```c++
   void swap(smart_ptr& rhs) 
   {
       using std::swap;
       swap(ptr_,rhs.ptr_);
       swap(shared_count_, rhs.shared_count_);
   }
   ```

7. 你需要对照修改拷贝构造函数和移动构造函数，为其添加引用计数？

   ```c++
   template <typename U>
   smart_ptr(const smart_ptr<U>& other){ 
       ptr_ = other.ptr_;
       if (ptr_)
       {
           other.shared_count_->add_count();
           shared_count_ = other.shared_count_;
       }
   }
   ```

8. 这里能够正确编译么？

   ```c++
   template <typename U>
   smart_ptr (const smart_ptr<U>& other) {
       ptr_ = other.ptr_;
       if (ptr_) {
           other.shared_count_->add_count();
           shared_count_ = other.shared_count_;
       }
   }
   
   template <typename U>
   smart_ptr (const smart_ptr<U>&& other) {
       ptr_ = other.ptr_;
       if (ptr_) {
           shared_count_ = other.shared_count_;
           ptr_ = nullptr;
       }
   }
   ```

9. 这里需要定义一个友元类？

   ```c++
   template <typename T>
   friend class smart_ptr;
   ```

10. 如何优化release函数手工释放的问题呢？

    ```c++
    long use_count() const {
        if (ptr_) {
            return shared_count_->get_count();
        } else {
            return 0;
        }
    }
    ```

11. 你可以简单写一个实列调用的函数么？

    ```c++
    class shape {
    public:
       virtual ~shape ()
    };
    
    class circle : shape { 
    public:
        ~shape () {
            puts("~cirlce ");
        }
    };
    
    int main() {
        smart_ptr<circle> ptr1(new circle);
        printf("use count of the ptr1 is %ld ", ptr1.use_count());
    
        smart_ptr<circle> ptr2;
        printf("use count of the ptr2 is %ld", ptr2.use_count());
    
        ptr2 = ptr1;
        printf("use count of the ptr2 is %ld", ptr2.use_count());
    
        if (ptr1) {
            printf("use count of the ptr1 is not empty");
        }
    }
    ```

12. 你可以实现一下dynamic_cast_ptr么，需要考虑那些，当然是需要支持模板的？

    ```c++
    template <typename T, typename U>
    smart_ptr<T> dynamic_cast_ptr (const smart_ptr<T>& other)
    {
        T* ptr = dynamic_cast<T*>(other.get());
        return smart_ptr<T>(other,ptr);
    }
    ```

13. 你觉得智能指针应该满足什么样的线程安全？

14. 从上面你能看出smart_ptr还缺点什么吗？

15. 你能实现一个string类么？

```c++
class String{
public:
    // 默认构造函数
    String(const char *str=nullptr);
    // 拷贝构造函数
    String(const String &str);
    // 析构函数
    ~String();
    // 字符串赋值函数
    String& operator =(const String& str);
private:
    char *m_data;
    int m_size;
};

// 构造函数
String::String(const char* str) {
    if (str == nullptr) {
        m_data = new char[1];
        // 这里是细节
        m_data[0] = '\0';
        m_size = 0;
    } else {
        len = strlen(str);
        m_data = new char[len+1];
        m_size = len;
        strcpy(m_data, str);
    }
}

// 拷贝构造函数
String::String(const String &str) {
    m_size = str.m_size;
    m_data = new char[m_size+1];
    // 这里依然是一个细节
    if (str.m_data != NULL) {
        strcpy(m_data, str.m_data);
    }
}
// 析构函数
String::~String() {
    delete[] m_data;
    m_size = 0;
}

// 赋值操作符有很多细节
// 考虑异常安全
String& String::operator =(const String &str) {
    // 防止自赋值
    if (&str != this) {
        String strTemp(str);

        // 这里为什么不直接使用new，防止内存不够，抛出异常
        char* pTemp = strTemp.m_data;
        strTemp.m_data = m_data;
        m_data = pTemp;
    }
    return *this;
}
```



## 03 | 右值和移动究竟解决了什么问题？

1. 你知道左值是什么？
   - 变量、函数或数据成员的名字
   - 返回左值引用的表达式，如++x、 x = 1、cout << ' '
   - 字符串变量如“hello world"
   - 左值是可以绑定左值引用的参数，如const T&
   
2. 那你还知道右值么？
   - 返回非引用类型的表达式，如x++、x+1、make_shared<int>(42)
   - 除字符字面量以外的字面量，如42、true
   
3. 那你说一下右值引用么？是什么样的形式？和左值有什么区别？

4. 你可以说一下移动的语义么？

   实现移动语义的主要意义是减少运行的开销，当然这个开销并不是很大。移动语义使得在C++里返回大对象（如容器）的函数和运算符成为现实，因而可以提高代码的简洁性和可读性，提高程序员的生产率。

5. 那你能说说如何实现移动么？

6. 如何避免在代码里出现`if （&rhs != this)`这样的判断？

   ```c++
   smart_ptr& operator=(smart_ptr rhs) noexcept
   {
       rhs.swap(*this);
       return *this;
   }
   ```

7. ` std::move`会不会妨碍返回值优化呢？

8. 引用折叠这个概念你清楚么？

9. 如果想左值依然保持左值，右值保持右值该用什么呢？

10. 为什么`smart_ptr::operator=`对左值和右值都有效，而且不需要对等号两边是否引用同一对象进行判断？

## 04 | 容器汇编 I：比较简单的若干容器

1. 你有使用`noexcept`关键字么？在拷贝构造和移动构造的时候有什么缺别？
2. 你熟悉的list成员函数有哪些呢？list底层实现是什么？
3. 你了解内存管理的栈和普通stack有什么区别么？

## 05 | 容器汇编 II：需要函数对象的容器

1. 你可以写一个关于`less`函数的模板么？

   ```c++
   template <class T>
   struct less:binary_function<T,T,bool> {
       bool operator() (const T& x,const T& y) const {
           return x < y;
       }
   };
   ```

## 06 | 异常：用还是不用，这是个问题

## 07 | 迭代器和好用的新for循环

1. 会写一个简洁的输入行迭代器么？

   ```c++
   for (const string& line:
           istream_line_reader(is)) {
               cout << line << endl;
   }
   ```

## 08 | 易用性改进 I：自动类型推断和初始化

1. 结构化绑定？

   ```c++
   auto [lower,upper] = mmp.equal_range("four");
   ```

## 09 | 易用性改进 II：字面量、静态断言和成员函数说明符

1. 二进制字面量有了解和使用么？
2. override和final 说明符有用过么？

## 10 | 到底应不应该返回对象？

## 11 | Unicode：进入多文字支持的世界

## 12 | 编译期多态：泛型编程和模板入门

## 13 | 编译期能做些什么？一个完整的计算世界

1. fmap函数模板编程会么？

   ```c++
   template < template <typename, typename>
           class OutContainer = vector,
           typename F, class R>
   auto fmap(F&& f, R&& inputs) 
   {
       typedef decay_t<decltype(
           f(*inputs.begin())) > 
           result_type;
           OutContainer<
           result_type,
           allocator<result_type>>
           result;
       for (auto&& item : inputs) {
           result.push_back(f(item));
       }
       return result;
   }
   ```

## 14 | SFINAE：不是错误的替换失败是怎么回事?

1. 编译期成员监测？
2. 标签分发理解么？

## 15 | constexpr：一个常态的世界

1. 如何检验一个constexpr函数能不能产生一个真正的编译器常量？

2. constexpr和const的区别？

3. 你能修正下满这个错误么？

   ```c++
   #include <iostream>
   #include <vector>
   
   struct magic {
       static const int number = 521;
   };
   
   int main() {
       std::vector<int> v;
       v.emplace_back(magic::number);
       std::cout << v[0] << std::endl;
   }
   ```

## 16 | 函数对象和lambda：进入函数式编程

1. 你可以简单的写一个Lambda表达式么？

   ```c++
   auto add_2 = [](int x) {
       return x + 2;
   };
   ```

   一个通用的adder

   ```c++
   auto adder = [](int n) {
       return [n](int x) {
           return x + n;
       };
   };
   ```

   `[](int x) { return x * x; } (3)`

   ```c++
   #include <array>
   #include <iostream>
   #include <numeric>
   
   using namespace std;
   
   int main() {
       array a{1, 2, 3, 4, 5};
       auto s = accumulate(
           a.begin(), a.end(), 0,
           [](auto x, auto y) {
               return x + y;
           });
       cout << s << endl;
   }
   ```

## 17 | 函数式编程：一种越来越流行的编程范式

1. 你能说说函数式编程的特点么？

## 18 | 应用可变模板和tuple的编译期技巧

1. 你会使用转发模板用法么？

   ```c++
   template <typename T, 
               typename... Args>
   inline unique_ptr<T>
   make_unique(Args&&... args)
   {
       return unique_ptr<T>(
           new T(forward<Args>(args)...));
   }
   // make_unique<vector<int>>(100,1);
   ```

2. 你可以用组合模板实现对下面的数组进行先平方，然后相加么？

   ```c++
   vector v{1,2,3,4,5};
   cout << squared_sum(v) << endl;
   // 55
   ```

## 19 | thread和future：领略异步中的未来

1. 你能写一个函数模板在析构时线程自动`join`么？

   ```c++
   #include <chrono>
   #include <iostream>
   #include <mutex>
   #include <thread>
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
   int main() {
       scoped_thread t1{func,"Henry"};
       scoped_thread t2{func, "Tien"};
       return 0;
   }
   ```

2. 你知道如何返回一个future么？

   ```c++
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
   ```

   上面的代码有什么问题么？`future`调用两次`get()`会发生什么？

3. 你知道promise怎么使用么？

   ```c++
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
   ```

4. `package_task` 和 `promise`和 `future`有什么区别呢？

   ```
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
   
       scoped_thread th{move(task)};
       this_thread::sleep_for(1s);
       cout << "I'am waitting for you\n";
       cout << "Answer: " << fut.get() << endl;
       return 0;
   }
   ```

   > 在调用 `f.get()` 之前，执行了 `std::packaged_task`，否则你的程序会一直阻塞在那。

   [区别][1]

   [异步编程](2)

## 20 | 内存模型和atomic：理解并发的复杂性



1. volatitle关键字了解二么？

2. 你知道如何在多线程内保证内存访问顺序吗？内存屏障有听说过么？

   ```c++
   #include<atomic>
   #include<iostream>
   using namespace std;
   int main() {
       atomic<int> y;
       int x =1;
       y.store(2,memory_order_release);
   
       if (y.load(memory_order_acquire) == 2) {
           x = 3;
           y.store(4,memory_order_relaxed);
       }
       return 0;
   }
   ```

3. 你可以实现一个`atomic`版本的线程安全单例？

   ```c++
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
   ```

4. 你会怎么样实现一个并发队列？

   - 对于单生产者、单消费者，可以用用原子量和获得、释放语义就能简单实现。
   - 对于多生产者、多消费者的情况，那么实现就比较复杂，一般会使用`compare_exchange_strong`或`compare_exchange_week`。

   [github参考1][4]

   [github参考2][3]

## 21 | 工具漫谈：编译、格式化、代码检查、排错各显身手

1. Clang-Format

   [clang-format](https://github.com/adah1972/nvwa/blob/master/.clang-format)

2. Cppcheck

3. Valgrind

4. Compiler Explorer

5. C++ Insight

## 22 | 处理数据类型变化和错误：optional、variant、expected和Herbception

1. optional 是干什么的呢？

2. variant和union有什么区别？

   ```c++
   #include<iostream>
   #include<string>
   #include<variant>
   using namespace std;
   int main() {
       
       variant<string,int,char> obj {
       "Hello World"};
       cout << get<string>(obj) << endl;
       return 0;
   }
   ```

## 23 | 数字计算：介绍线性代数和数值计算库

1. Armadillo

   CentOS下安装：`sudo yum install armadillo-devel`

   MacOS下安装：`brew install armadillo`

## 24 | Boost：你需要的“瑞士军刀”

1. Boost.TypeIndex
2. Boost::noncopyble
3. Boost::static_assert 编译器断言

## 27 | C++ REST SDK：使用现代C++开发网络应用



## 28 | Concepts：如何对模板进行约束?

1. 你有了解concepts么？

   从基本概念上来讲，“概念”就是一组对模板参数的约束条件。
   
   

## 参考资料

[1]:https://blog.csdn.net/weiwei9363/article/details/106418146	"csdn"
[2]: https://zhuanlan.zhihu.com/p/78612487	"知乎"
[3]:https://github.com/cameron314/concurrentqueue	"无锁多生产者多消费者并发队列"
[4]:https://github.com/adah1972/nvwa/blob/master/nvwa/fc_queue.h	"单生产者单消费者并发队列"










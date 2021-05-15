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

9. 如果想左值依然保持左值，右值保持又值改用什么呢？

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

2. 


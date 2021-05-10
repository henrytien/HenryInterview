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

   


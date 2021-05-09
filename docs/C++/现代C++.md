## **01 |** 堆、栈、RAII : C++ 里该如何管理资源?

1. **RAII**是什么呢？
2. 栈的增长方向是？

## 02 | **自己动手，实现** C++ 的智能指针

1. 请看下面这段代码和智能指针有什么缺别？

   ```c++
   template <typename T>
   class smart_ptr{
   public:
   	explicit smart_ptr(T* ptr = nullptr)
       :ptr_(ptr){}
     ~smart_ptr(){
       delete ptr_;
     }
     
    // smart_ptr(const smart_ptr&) = delete;
    // smart_ptr& operator=(const smart_ptr&) = delete;
    smart_ptr(smart_ptr&& other) 
    {
    		ptr_ = other.release();  
    } 
    smart_ptr& operator=(smart_ptr rhs)
    {
      rhs.swap(*this);
      return *this;
    }
    
    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    operator bool() const { return ptr_; }
    T* get() const { return ptr_; }
   private:
     T* ptr_;
   }
   
   int main() {
     smart_ptr<shape> ptr1{create_shape(shape_type::cycle)};
     smart_ptr<shape> ptr2{ptr1}; //编译错误
     smart_ptr<shape> ptr3;
     
     ptr3 = ptr1;	// 编译错误
     ptr3 = std::move(ptr1); // ok
     smart_ptr<shape> ptr4{std::move(ptr3)}; // ok
     // 这里你看出这个类似哪个智能指针的行为了呢？
   }
   ```

   

2. 
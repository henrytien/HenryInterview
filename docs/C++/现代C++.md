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
    T* get() const { return ptr_; }
   private:
     T* ptr_;
   }
   ```

   

2. 
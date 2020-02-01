##  C/C++

### const

#### 作用

1. 修饰变量，说明该变量不可以被改变；
2. 修饰指针，分为指向常量的指针和指针常量；
3. 常量引用，经常用于形参类型，即避免了拷贝，又避免了函数对值的修改；
4. 修饰成员函数，说明该成员函数内不能修改成员变量。


### static

#### 作用
1. 修饰普通变量，修改变量的存储区域和生命周期，使变量存储在静态区，在 main 函数运行前就分配了空间，如果有初始值就用初始值初始化它，如果没有初始值系统用默认值初始化它。
2. 修饰普通函数，表明函数的作用范围，仅在定义该函数的文件内才能使用。在多人开发项目时，为了防止与他人命名空间里的函数重名，可以将函数定位为 static。
3. 修饰成员变量，修饰成员变量使所有的对象只保存一个该变量，而且不需要生成对象就可以访问该成员。
4. 修饰成员函数，修饰成员函数使得不需要生成对象就可以访问该函数，但是在 static 函数内不能访问非静态成员。


### Difference Between Malloc and New

> The basic differences between the two is that malloc exits in the C-language while new is a specific feauture of the C++ language. Malloc is also a function(which, for programmers, requires some time to execute) while new is an operator program (which cuts the execution time). This is a benefit from the operator new because programmers doing real-time programming have a need to choose the fastest method to use.

> Operator new is type-safe unlike the function malloc.

> The two also have different ways in dealing with failure and memory exhaustion.

> Function malloc doesn't construct an object(called constructor of object) but operator new does.

> Memory can also be re-sized or reallocated by using function malloc by using realloc. 

[Read more: Difference Between Malloc and New](http://www.differencebetween.net/technology/software-technology/difference-between-malloc-and-new/#ixzz6Cgc5Ovu6)

[What is the difference between new/delete and malloc/free?
](https://stackoverflow.com/questions/240212/what-is-the-difference-between-new-delete-and-malloc-free?r=SearchResults)
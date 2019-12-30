# README

目前mac编译成功，目标Windows，Linux

`vcpkg install folly`

[使用clion+cmake+vcpkg的开发现代的c++跨平台程序](https://www.cnblogs.com/Leo_wl/p/11555600.html)


### code

std::move
在C++11中，标准库在<utility>中提供了一个有用的函数std::move，std::move并不能移动任何东西，它唯一的功能是将一个左值强制转化为右值引用，继而可以通过右值引用使用该值，以用于移动语义。从实现上讲，std::move基本等同于一个类型转换：static_cast<T&&>(lvalue);
https://blog.csdn.net/p942005405/article/details/84644069
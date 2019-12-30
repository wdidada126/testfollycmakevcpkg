# README

目前mac编译成功，目标Windows，Linux

`vcpkg install folly`

[使用clion+cmake+vcpkg的开发现代的c++跨平台程序](https://www.cnblogs.com/Leo_wl/p/11555600.html)


### code

std::move
在C++11中，标准库在<utility>中提供了一个有用的函数std::move，std::move并不能移动任何东西，它唯一的功能是将一个左值强制转化为右值引用，继而可以通过右值引用使用该值，以用于移动语义。从实现上讲，std::move基本等同于一个类型转换：static_cast<T&&>(lvalue);
https://blog.csdn.net/p942005405/article/details/84644069

[使用cmake和gtest来规划单元测试](https://menrfa.wordpress.com/2012/02/09/%E4%BD%BF%E7%94%A8cmake%E5%92%8Cgtest%E6%9D%A5%E8%A7%84%E5%88%92%E5%8D%95%E5%85%83%E6%B5%8B%E8%AF%95/)


```shell script

====================[ Build | sample1_unittest | Debug ]========================
/usr/local/bin/cmake --build /Users/ibqo/CLionProjects/testfollycmakevcpkg/cmake-build-debug --target sample1_unittest -- -j 4
[ 50%] Linking CXX executable sample1_unittest
Undefined symbols for architecture x86_64:
  "IsPrime(int)", referenced from:
      (anonymous namespace)::IsPrimeTest_Negative_Test::TestBody() in sample1_unittest.cc.o
      (anonymous namespace)::IsPrimeTest_Trivial_Test::TestBody() in sample1_unittest.cc.o
      (anonymous namespace)::IsPrimeTest_Positive_Test::TestBody() in sample1_unittest.cc.o
  "Factorial(int)", referenced from:
      (anonymous namespace)::FactorialTest_Negative_Test::TestBody() in sample1_unittest.cc.o
      (anonymous namespace)::FactorialTest_Zero_Test::TestBody() in sample1_unittest.cc.o
      (anonymous namespace)::FactorialTest_Positive_Test::TestBody() in sample1_unittest.cc.o
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make[3]: *** [sample1_unittest] Error 1
make[2]: *** [CMakeFiles/sample1_unittest.dir/all] Error 2
make[1]: *** [CMakeFiles/sample1_unittest.dir/rule] Error 2
make: *** [sample1_unittest] Error 2

```

[Mac下Clion编译错误：Undefined symbols for architecture x86_64](https://blog.csdn.net/iamoldpan/article/details/78258107)
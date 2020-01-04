# README

- folly
-wangle
- gtest


### folly
目前mac编译成功，目标Windows，Linux

`vcpkg install folly`

folly版本
2019.10.21.00

https://github.com/facebook/folly/blob/v2019.10.21.00/folly/docs/Overview.md

- AtomicHashMap

[使用clion+cmake+vcpkg的开发现代的c++跨平台程序](https://www.cnblogs.com/Leo_wl/p/11555600.html)


### code

std::move
在C++11中，标准库在<utility>中提供了一个有用的函数std::move，std::move并不能移动任何东西，它唯一的功能是将一个左值强制转化为右值引用，继而可以通过右值引用使用该值，以用于移动语义。从实现上讲，std::move基本等同于一个类型转换：static_cast<T&&>(lvalue);

[c++ 之 std::move 原理实现与用法总结](https://blog.csdn.net/p942005405/article/details/84644069)

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

cmake如何自动运行gtest测试

[建立简单的带单元测试的CMake项目](https://www.blurredcode.com/2019/03/452/)

make test
运行测试

[cmake处理多源文件目录的方法](https://www.cnblogs.com/fnlingnzb-learner/p/7202236.html]

子文件夹
CMakeLists.txt add_execute失败


[wangle examples](https://github.com/facebook/wangle/tree/master/wangle/example)


- RpcServer
- RpcClient
使用了thrift folley wangle的例子

```shell script
vcpkg install thrift
Your feedback is important to improve Vcpkg! Please take 3 minutes to complete our survey by running: vcpkg contact --survey
The following packages will be built and installed:
    thrift[core]:x64-osx
Starting package 1/1: thrift:x64-osx
Building package thrift[core]:x64-osx...
-- Using cached /Users/ibqo/vcpkg/downloads/apache-thrift-acdd4226c210336e9e15eb812e5932a645fcd5ce.tar.gz
-- Using source at /Users/ibqo/vcpkg/buildtrees/thrift/src/a645fcd5ce-616856a2c8
-- Configuring x64-osx-dbg
-- Configuring x64-osx-rel
-- Building x64-osx-dbg
CMake Error at scripts/cmake/vcpkg_execute_build_process.cmake:136 (message):
    Command failed: /Users/ibqo/vcpkg/downloads/tools/cmake-3.14.0-osx/cmake-3.14.0-Darwin-x86_64/CMake.app/Contents/bin/cmake --build . --config Debug --target install -- -v
    Working Directory: /Users/ibqo/vcpkg/buildtrees/thrift/x64-osx-dbg
    See logs for more information:
      /Users/ibqo/vcpkg/buildtrees/thrift/install-x64-osx-dbg-out.log

Call Stack (most recent call first):
  scripts/cmake/vcpkg_build_cmake.cmake:91 (vcpkg_execute_build_process)
  scripts/cmake/vcpkg_install_cmake.cmake:24 (vcpkg_build_cmake)
  ports/thrift/portfile.cmake:45 (vcpkg_install_cmake)
  scripts/ports.cmake:94 (include)


Error: Building package thrift:x64-osx failed with: BUILD_FAILED
Please ensure you're using the latest portfiles with `.\vcpkg update`, then
submit an issue at https://github.com/Microsoft/vcpkg/issues including:
  Package: thrift:x64-osx
  Vcpkg version: 2019.09.12-unknownhash

Additionally, attach any relevant sections from the log files above.
```

### cpp
c++的class不能用public修饰

#pragma once
相当于只引用一次
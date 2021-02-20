cmake_minimum_required(VERSION 3.15)
project(testfollycmakevcpkg)

set(CMAKE_CXX_STANDARD 14)

ADD_SUBDIRECTORY(mylibrary)

add_library(mylibrary  mylibrary/MyClass.cpp mylibrary/MyClass.h)

add_executable(testfollycmakevcpkg src/main.cpp)
add_executable(RpcClient RpcClient.cpp)
add_executable(RpcServer RpcServer.cpp)

add_executable(testfollycmakevcpkgTest test/gtestmain.cpp)


find_package(folly CONFIG REQUIRED)
add_executable(TestConcurrentHashMap TestFolly/ConcurrentHashMap.cpp)
#add_executable(AtomicHashMapTest TestFolly/AtomicHashMapTest.cpp)# undefine reference


target_link_libraries(TestConcurrentHashMap PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)
#target_link_libraries(AtomicHashMapTest PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)



target_link_libraries(testfollycmakevcpkg PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)

enable_testing()

find_package(GTest CONFIG REQUIRED)
target_link_libraries(testfollycmakevcpkgTest PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(AllTestsInMain testfollycmakevcpkgTest)


find_package(wangle REQUIRED)
target_link_libraries(RpcClient PRIVATE wangle::wangle)
target_link_libraries(RpcServer PRIVATE wangle::wangle)
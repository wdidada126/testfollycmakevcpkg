cmake_minimum_required(VERSION 3.15)
project(testfollycmakevcpkg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(mylibrary  mylibrary/MyClass.cpp mylibrary/MyClass.h)

add_executable(testfollycmakevcpkg src/main.cpp)
#add_executable(RpcClient RpcClient.cpp)
#add_executable(RpcServer RpcServer.cpp)

add_executable(gtestmethods test/gtestmain.cpp)
add_executable(gtestpairTest test/gtestpair.cpp)


find_package(folly CONFIG REQUIRED)
add_executable(TestConcurrentHashMap TestFolly/ConcurrentHashMap.cpp)
#add_executable(AtomicHashMapTest TestFolly/AtomicHashMapTest.cpp)# undefined reference


#add_executable(FBStringBenchmark TestFolly/FBStringBenchmark.cpp)# TestFolly/FBStringBenchmark.cpp:81:10: fatal error: 'folly/test/FBStringTestBenchmarks.cpp.h' file not found
#target_link_libraries(FBStringBenchmark PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)


target_link_libraries(TestConcurrentHashMap PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)
#target_link_libraries(AtomicHashMapTest PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)



target_link_libraries(testfollycmakevcpkg PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)

enable_testing()

find_package(GTest CONFIG REQUIRED)
target_link_libraries(gtestmethods PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
target_link_libraries(gtestpairTest PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(AllTestsInMain testfollycmakevcpkgTest)


#find_package(wangle REQUIRED)
#target_link_libraries(RpcClient PRIVATE wangle::wangle)
#target_link_libraries(RpcServer PRIVATE wangle::wangle)
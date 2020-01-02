cmake_minimum_required(VERSION 3.15)
project(testfollycmakevcpkg)

set(CMAKE_CXX_STANDARD 14)

ADD_SUBDIRECTORY(mylibrary)

add_library(mylibrary  mylibrary/MyClass.cpp mylibrary/MyClass.h)

add_executable(testfollycmakevcpkg src/main.cpp)
add_executable(RpcClient RpcClient.cpp)
add_executable(RpcServer RpcServer.cpp)
add_executable(testfollycmakevcpkgTest test/gtestmain.cpp)
add_executable(sample1_unittest samples/sample1_unittest.cc samples/sample1.cc)
add_executable(sample2_unittest samples/sample2_unittest.cc samples/sample2.cc)
add_executable(sample3_unittest samples/sample3_unittest.cc)
add_executable(sample4_unittest samples/sample4_unittest.cc samples/sample4.cc)
add_executable(sample5_unittest samples/sample3_unittest.cc samples/sample5_unittest.cc samples/sample1_unittest.cc)

add_executable(TestConcurrentHashMap TestFolly/ConcurrentHashMap.cpp)

target_link_libraries(TestConcurrentHashMap PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)


find_package(folly CONFIG REQUIRED)
target_link_libraries(testfollycmakevcpkg PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)

enable_testing()

find_package(GTest CONFIG REQUIRED)
target_link_libraries(testfollycmakevcpkgTest PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(AllTestsInMain testfollycmakevcpkgTest)

target_link_libraries(sample1_unittest PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
target_link_libraries(sample2_unittest PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
target_link_libraries(sample3_unittest PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
target_link_libraries(sample4_unittest PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
target_link_libraries(sample5_unittest PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(AllTestsInMain sample1_unittest)
add_test(AllTestsInMain sample2_unittest)
add_test(AllTestsInMain sample3_unittest)
add_test(AllTestsInMain sample4_unittest)
add_test(AllTestsInMain sample5_unittest)

find_package(wangle REQUIRED)
target_link_libraries(RpcClient PRIVATE wangle::wangle)
target_link_libraries(RpcServer PRIVATE wangle::wangle)
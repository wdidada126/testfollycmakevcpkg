cmake_minimum_required(VERSION 3.15)
project(testfollycmakevcpkg)

set(CMAKE_CXX_STANDARD 14)

add_executable(testfollycmakevcpkg src/main.cpp)
add_executable(testfollycmakevcpkgTest test/gtestmain.cpp)
find_package(folly CONFIG REQUIRED)
target_link_libraries(testfollycmakevcpkg PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)

enable_testing()

find_package(GTest CONFIG REQUIRED)
target_link_libraries(testfollycmakevcpkgTest PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(AllTestsInMain testfollycmakevcpkgTest)

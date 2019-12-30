cmake_minimum_required(VERSION 3.15)
project(testfollycmakevcpkg)

set(CMAKE_CXX_STANDARD 14)

add_executable(testfollycmakevcpkg main.cpp)
find_package(folly CONFIG REQUIRED)
target_link_libraries(testfollycmakevcpkg PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)
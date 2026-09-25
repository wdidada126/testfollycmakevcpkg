cmake_minimum_required(VERSION 3.18)
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
if(NOT TARGET folly::folly AND TARGET Folly::folly)
    add_library(folly::folly ALIAS Folly::folly)
endif()
add_executable(TestConcurrentHashMap TestFolly/ConcurrentHashMap.cpp)
#add_executable(AtomicHashMapTest TestFolly/AtomicHashMapTest.cpp)# undefined reference

# folly::AtomicIntrusiveHashMap 不存在于开源 folly（见 TestFolly/AtomicIntrusiveHashMap.md），
# 实测其真实存在的家族成员 AtomicIntrusiveLinkedList
add_executable(atomic_intrusive_list_test TestFolly/AtomicIntrusiveHashMapTest.cpp)


#add_executable(FBStringBenchmark TestFolly/FBStringBenchmark.cpp)# TestFolly/FBStringBenchmark.cpp:81:10: fatal error: 'folly/test/FBStringTestBenchmarks.cpp.h' file not found
#target_link_libraries(FBStringBenchmark PRIVATE folly::folly)


target_link_libraries(TestConcurrentHashMap PRIVATE folly::folly)
target_link_libraries(atomic_intrusive_list_test PRIVATE folly::folly)
#target_link_libraries(AtomicHashMapTest PRIVATE folly::folly)



target_link_libraries(testfollycmakevcpkg PRIVATE folly::folly)
add_executable(f_a_list src/f_a_list.cpp)
target_link_libraries(f_a_list PRIVATE folly::folly)
add_executable(clh_example src/clh_example.cpp)
target_link_libraries(clh_example PRIVATE folly::folly)
add_executable(folly_d_mutex src/folly_d_mutex.cpp)
target_link_libraries(folly_d_mutex PRIVATE folly::folly)

enable_testing()

find_package(GTest CONFIG REQUIRED)
if(NOT TARGET gtest::gtest AND TARGET GTest::gtest)
    add_library(gtest::gtest ALIAS GTest::gtest)
endif()
# tests define their own main (do NOT add GTEST_API_ to it: it expands to dllimport on MSVC)
target_link_libraries(gtestmethods PRIVATE GTest::gtest)
target_link_libraries(gtestpairTest PRIVATE GTest::gtest)

add_test(AllTestsInMain gtestmethods)
add_test(AllTestsInPair gtestpairTest)
add_test(FollyIntrusiveLinkedList atomic_intrusive_list_test)


#find_package(wangle REQUIRED)
#target_link_libraries(RpcClient PRIVATE wangle::wangle)
#target_link_libraries(RpcServer PRIVATE wangle::wangle)

cmake_minimum_required(VERSION 3.17)

project(Test)

enable_testing()

set(gtest_disable_pthreads on) #needed in MinGW

add_executable(runUnitTests gtest.cpp)
target_link_libraries(runUnitTests gtest gtest_main)
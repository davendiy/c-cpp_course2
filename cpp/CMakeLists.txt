cmake_minimum_required(VERSION 3.13)
project(cpp)

set(CMAKE_CXX_STANDARD 98)

set(BUILD_1 main)
set(SOURCE_FILES_1 main.cpp)
add_executable(${BUILD_1} ${SOURCE_FILES_1})

set(BUILD_2 test)
set(SOURCE_FILES_2 test.cpp)
add_executable(${BUILD_2} ${SOURCE_FILES_2})

set(BUILD_3 Chapter3_basic)
set(SOURCE_FILES_3 chapter3_basic/homework.cpp)
add_executable(${BUILD_3} ${SOURCE_FILES_3})

set(BUILD_4 Chapter4_if_else)
set(SOURCE_FILES_4 chapter4_if_else/homework.cpp)
add_executable(${BUILD_4} ${SOURCE_FILES_4})

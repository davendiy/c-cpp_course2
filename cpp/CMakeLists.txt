cmake_minimum_required(VERSION 3.13)
project(cpp)

set(CMAKE_CXX_STANDARD 98)

set(BUILD_1 main)
set(SOURCE_FILES_1 main.cpp)
add_executable(${BUILD_1} ${SOURCE_FILES_1})

set(BUILD_2 test)
set(SOURCE_FILES_2 test.cpp)
add_executable(${BUILD_2} ${SOURCE_FILES_2})

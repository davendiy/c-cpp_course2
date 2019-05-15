cmake_minimum_required(VERSION 3.14)
project(cpp_project)

set(CMAKE_CXX_STANDARD 11)

add_executable(cpp_project main.cpp)
add_library(tensor tensor.cpp)
target_link_libraries(cpp_project tensor)

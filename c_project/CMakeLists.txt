cmake_minimum_required(VERSION 3.14)
project(c_project C)

set(CMAKE_C_STANDARD 99)

add_executable(c_project main.c)

add_library(bigNumber STATIC BigNumbers.c)
set_target_properties(bigNumber PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(c_project bigNumber)

cmake_minimum_required(VERSION 3.14)
project(c_project C)

set(CMAKE_C_STANDARD 99)

add_executable(c_project main.c src/BigNumbers.c)
add_executable(test tests/tests.c src/BigNumbers.c)

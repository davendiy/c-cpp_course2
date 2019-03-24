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

set(BUILD_5 Chapter5_cycles)
set(SOURCE_FILES_5 chapter5_cycles/homework.cpp)
add_executable(${BUILD_5} ${SOURCE_FILES_5})

set(BUILD_6 Chapter6_functions)
set(SOURCE_FILES_6 chapter6_functions/homework.cpp)
add_executable(${BUILD_6} ${SOURCE_FILES_6})

set(BUILD_7 Chapter7_switch)
set(SOURCE_FILES_7 chapter7_switch/homework.cpp)
add_executable(${BUILD_7} ${SOURCE_FILES_7})

set(BUILD_8 Chapter7_switch2)
set(SOURCE_FILES_8 chapter7_switch/tictactoe.cpp)
add_executable(${BUILD_8} ${SOURCE_FILES_8})

set(BUILD_9 Chapter8_random)
set(SOURCE_FILES_9 chapter8_random/homework.cpp)
add_executable(${BUILD_9} ${SOURCE_FILES_9})

set(BUILD_10 Chapter10_arrays)
set(SOURCE_FILES_10 chapter10_arrays/homework.cpp)
add_executable(${BUILD_10} ${SOURCE_FILES_10})

set(BUILD_11 Chapter11_structs)
set(SOURCE_FILES_11 chapter11_structs/homework.cpp)
add_executable(${BUILD_11} ${SOURCE_FILES_11})

set(BUILD_12 Chapter13_pointers)
set(SOURCE_FILES_12 chapter13_pointers/homework.cpp)
add_executable(${BUILD_12} ${SOURCE_FILES_12})

set(BUILD_13 Chapter13_pointers2)
set(SOURCE_FILES_13 chapter13_pointers/practice.cpp)
add_executable(${BUILD_13} ${SOURCE_FILES_13})

set(BUILD_14 stack)
set(SOURCE_FILES_14 stack1.cpp)
add_executable(${BUILD_14} ${SOURCE_FILES_14})

set(BUILD_15 dynamyc)
set(SOURCE_FILES_15 chapter14_dynamic/homework.cpp)
add_executable(${BUILD_15} ${SOURCE_FILES_15})

set(BUILD_16 dynamyc2)
set(SOURCE_FILES_16 chapter14_dynamic/practice.cpp)
add_executable(${BUILD_16} ${SOURCE_FILES_16})

set(BUILD_17 list)
set(SOURCE_FILES_17 list.cpp)
add_executable(${BUILD_17} ${SOURCE_FILES_17})

set(BUILD_18 samsung)
set(SOURCE_FILES_18 samsung_task.cpp)
add_executable(${BUILD_18} ${SOURCE_FILES_18})

set(BUILD_19 samsung2)
set(SOURCE_FILES_19 samsung_tmp.cpp)
add_executable(${BUILD_19} ${SOURCE_FILES_19})

set(BUILD_20 chapter17_binary_trees)
set(SOURCE_FILES_20 chapter17_binary_trees/practice.cpp)
add_executable(${BUILD_20} ${SOURCE_FILES_20})

set(BUILD_21 chapter18_stl)
set(SOURCE_FILES_21 chapter18_stl/practice.cpp)
add_executable(${BUILD_21} ${SOURCE_FILES_21})

set(BUILD_22 chapter24_classes)
set(SOURCE_FILES_22 chapter24_classes/first.cpp)
add_executable(${BUILD_22} ${SOURCE_FILES_22})

set(BUILD_23 chapter24_classes2)
set(SOURCE_FILES_23 chapter24_classes/vectorOfInt.cpp)
add_executable(${BUILD_23} ${SOURCE_FILES_23})


project(vectorOfInt)
set(SOURCE_LIB chapter24_classes/vectorOfInt.cpp)
set(SOURCE_TEST chapter24_classes/test.cpp)
add_library(vectorOfInt STATIC ${SOURCE_LIB})
add_executable(test_vector ${SOURCE_TEST})
target_link_libraries(test_vector vectorOfInt)


add_executable(chapter26_polymorph_practice chapter26_polymorph/practic.cpp)

add_executable(chapter26_homework chapter26_polymorph/homework.cpp)

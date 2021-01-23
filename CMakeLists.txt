cmake_minimum_required(VERSION 3.17)
project(cpp_semester_5)

set(CMAKE_CXX_STANDARD 17)

add_executable(task_1 task_1/main.cpp)
add_executable(task_2 task_2/main.cpp task_2/utils.h task_2/sort.h)
add_executable(task_3 task_3/main.cpp task_3/box.h task_3/box.cpp task_3/editor.h task_3/editor.cpp task_3/utils.h)
add_executable(task_4 task_4/main.cpp task_4/visitor.h task_4/assembler.h task_4/ast_node.h task_4/ast_node.cpp task_4/assembler.cpp)

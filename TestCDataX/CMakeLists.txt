cmake_minimum_required(VERSION 3.10.0)
project(TestCDataX VERSION 0.1.0 LANGUAGES C)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/../src SRC)
add_executable(TestCDataX main.c ${SRC})

target_include_directories(TestCDataX PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../include)
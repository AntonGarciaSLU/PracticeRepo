cmake_minimum_required(VERSION 3.22)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled src/main.c src/library.c include/library.h)

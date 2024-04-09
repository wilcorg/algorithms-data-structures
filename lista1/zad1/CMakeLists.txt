cmake_minimum_required(VERSION 3.27)
project(1z)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "-O3")

add_executable(1z main.c
        stack.c
        stack.h
        optional.h
        queue.h
        queue.c)

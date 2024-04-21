cmake_minimum_required(VERSION 3.27)
project(arr_sort)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(arr_sort main.cpp
        Sorts.cpp
        Sorts.hpp
        SortUtils.cpp
        SortUtils.hpp
        SortUtils.cpp)

target_include_directories(arr_sort PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(arr_sort ${Boost_LIBRARIES})

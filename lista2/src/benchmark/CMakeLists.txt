cmake_minimum_required(VERSION 3.27)
project(benchmark)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(benchmark main.cpp
        BenchUtils.hpp
        BenchUtils.cpp
        include/SortUtils.cpp
        include/GenUtils.cpp
        include/Sorts.hpp
        include/Sorts.cpp
)

target_include_directories(benchmark PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(benchmark ${Boost_LIBRARIES})

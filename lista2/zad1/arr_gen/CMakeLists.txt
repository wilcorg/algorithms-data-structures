cmake_minimum_required(VERSION 3.27)
project(arr_gen)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(arr_gen main.cpp)

target_include_directories(arr_gen PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(arr_gen ${Boost_LIBRARIES})

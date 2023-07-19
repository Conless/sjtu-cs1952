cmake_minimum_required(VERSION 3.11)
project(brick_out_simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g")

add_executable(brick_out_simulator main.cpp)
add_executable(test test.cpp)

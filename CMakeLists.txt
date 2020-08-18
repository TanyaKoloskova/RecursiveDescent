cmake_minimum_required(VERSION 3.15)
project(made1_calculator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined")

add_executable(made1_calculator main.cpp Recursive_descent-calculator.cpp Recursive_descent-calculator.h)
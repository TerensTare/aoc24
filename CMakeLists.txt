
cmake_minimum_required(VERSION 3.20)

project(aoc24)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(day1 day1/main.cpp)

get_target_property(day1_out day1 BINARY_DIR)
configure_file("day1/input.txt" "${day1_out}/input.txt" COPYONLY)
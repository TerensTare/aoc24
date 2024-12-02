
cmake_minimum_required(VERSION 3.20)

project(aoc24)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

foreach(i RANGE 1 25)
    if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/day${i}/")
        add_executable("day${i}" "day${i}/main.cpp")

        add_custom_command(
            TARGET "day${i}" POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/day${i}/input.txt
            $<TARGET_FILE_DIR:day${i}>/input.txt
        )
    endif()
endforeach()
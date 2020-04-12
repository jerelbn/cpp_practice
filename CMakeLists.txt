cmake_minimum_required(VERSION 2.6)
project(practice)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
    message(STATUS "Build type: Release")
endif()
set(CMAKE_CXX_STANDARD 11)

add_executable(shared_ptr src/shared_ptr.cpp)
add_executable(circular_buffer src/circular_buffer.cpp)

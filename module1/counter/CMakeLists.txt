cmake_minimum_required(VERSION 3.8)
project(counter)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(counter ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.20)
project(http_demo)

set(CMAKE_CXX_STANDARD 17)

add_executable(http_demo main.cpp)
target_include_directories(http_demo PRIVATE include)

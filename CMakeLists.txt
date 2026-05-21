cmake_minimum_required(VERSION 4.1)
project(toyRenderer_web)

set(CMAKE_CXX_STANDARD 20)

add_executable(toyRenderer_web main.cpp
        counter.cpp)

include_directories(${EMSDK_INCLUDE_DIR})
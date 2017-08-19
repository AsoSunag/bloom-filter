cmake_minimum_required(VERSION 3.4.1)

project(bloom-filter)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-Wall -fno-rtti")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(
    bloom-filter
)

add_executable(bloom-filter
    bloom-filter/main.cpp
)

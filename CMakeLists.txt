cmake_minimum_required(VERSION 3.30)
project(PS3UpdateSwapper VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist)

add_executable(PS3UpdateSwapper src/ps3updateswapper.cpp)

include_directories(src)

install(TARGETS PS3UpdateSwapper DESTINATION bin)

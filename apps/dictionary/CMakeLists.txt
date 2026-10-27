
cmake_minimum_required(VERSION 3.16)

project(dictionary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(dictionary main.cpp)

target_include_directories(dictionary PRIVATE ../../include)

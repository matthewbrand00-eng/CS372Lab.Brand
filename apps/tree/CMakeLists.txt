
cmake_minimum_required(VERSION 3.16)

project(tree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tree main.cpp)

target_include_directories(tree PRIVATE ../../include)

target_link_libraries(tree PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tree)

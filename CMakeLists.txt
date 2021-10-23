cmake_minimum_required(VERSION 3.0.0)
project(nd3_1 VERSION 1.0.0)

include(CTest)
enable_testing()

add_executable(nd3_1 main.cpp banker.h timeout.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
include(CPack)

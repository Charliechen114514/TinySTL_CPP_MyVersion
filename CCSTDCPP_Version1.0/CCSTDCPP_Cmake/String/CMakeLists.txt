cmake_minimum_required(VERSION 3.24)
project(String)

set(CMAKE_CXX_STANDARD 20)

add_executable(String test.cpp CCSTDCPP_String.hpp)

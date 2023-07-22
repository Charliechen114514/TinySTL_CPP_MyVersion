cmake_minimum_required(VERSION 3.24)
project(Vector)

set(CMAKE_CXX_STANDARD 23)

add_executable(Vector CCSTDCPP_Vector.hpp  FunctionalizeClass.hpp staticArray.hpp testcpp.cpp)

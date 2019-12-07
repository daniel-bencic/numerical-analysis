cmake_minimum_required(VERSION 3.14.6)
project(numerical-analysis)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(numerical-analysis src/main.cc)

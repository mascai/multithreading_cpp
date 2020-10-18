cmake_minimum_required(VERSION 3.18)

project(Process)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# simplify include ("process_lib/include/process.h" --> "process.h")
include_directories(process_lib/include/)

add_library(process process_lib/src/process.cpp)
add_executable(demo main.cpp)
target_link_libraries(demo process)

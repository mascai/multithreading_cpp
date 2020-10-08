cmake_minimum_required(VERSION 3.18)

project(Process)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(process.bin  process_lib/include/process.h process_lib/src/process.cpp  main.cpp)


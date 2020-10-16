cmake_minimum_required(VERSION 3.18)

project(Logger)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(log_lib log/src/log.cpp)
add_library(file_logger_lib log/src/FileLogger.cpp)

add_executable(demo main.cpp)
target_link_libraries(demo log_lib file_logger_lib)

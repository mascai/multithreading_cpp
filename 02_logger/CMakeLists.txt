cmake_minimum_required(VERSION 3.18)

project(Logger)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(log/include/)

add_library(log_lib log/src/log.cpp log/src/FileLogger.cpp log/src/StdoutLogger.cpp log/src/StderrLogger.cpp)

add_executable(demo main.cpp)
target_link_libraries(demo log_lib)

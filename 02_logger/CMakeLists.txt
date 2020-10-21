cmake_minimum_required(VERSION 3.18)

project(Logger)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(log)

target_include_directories(log_lib PUBLIC log/include)

add_executable(demo main.cpp)
target_link_libraries(demo log_lib)

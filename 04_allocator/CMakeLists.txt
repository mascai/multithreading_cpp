cmake_minimum_required(VERSION 3.18)

project(SharedMap)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(shmem)

add_executable(demo main.cpp)
target_link_libraries(demo shmem_lib)

target_include_directories(shmem_lib PUBLIC shmem/include)

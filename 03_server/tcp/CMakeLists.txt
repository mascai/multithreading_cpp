cmake_minimum_required(VERSION 3.18)

project(TcpServer)

set(LIB_SRC src/Descriptor.cpp src/tcp.cpp)
add_library(tcp_lib ${LIB_SRC})

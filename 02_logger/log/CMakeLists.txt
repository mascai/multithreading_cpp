cmake_minimum_required(VERSION 3.18)

project(Logger)

add_library(log_lib src/log.cpp src/FileLogger.cpp src/StdoutLogger.cpp src/StderrLogger.cpp)

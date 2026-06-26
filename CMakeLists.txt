cmake_minimum_required(VERSION 4.2)
project(simplescreencapture)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE .)


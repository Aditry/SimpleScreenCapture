cmake_minimum_required(VERSION 3.20)

project(simplescreencapture LANGUAGES CXX)

add_library(ssc INTERFACE)

target_compile_features(ssc INTERFACE cxx_std_20)

target_include_directories(ssc INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


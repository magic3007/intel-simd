cmake_minimum_required(VERSION 3.0)

project(intel-simd LANGUAGES CXX)

include_directories(3rd)

add_executable(demo
        main.cpp yuv_420.cpp rgb.cpp)
cmake_minimum_required(VERSION 3.0)

project(intel-simd)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(SSE)

include_directories(3rd)

add_executable(demo
        main.cpp yuv_420.cpp rgb.cpp)
target_compile_options(demo PRIVATE "SHELL: ${SSE_COMPILER_FLAGS}")
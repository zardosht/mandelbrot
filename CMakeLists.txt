cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(CppND_Capstone)

find_path(SIFTGPU_INCLUDE_DIR FreeImage.h)
find_library(SIFTGPU_LIBRARY libfreeimage)
include_directories(${SIFTGPU_INCLUDE_DIR})


add_executable(mandelbrot src/main 
                          src/mandelbrot.cpp)
target_link_libraries(mandelbrot freeimage)

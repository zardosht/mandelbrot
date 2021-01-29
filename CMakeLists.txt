cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall -pthread")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS} -pthread" )

project(CppND_Capstone)

find_package(OpenCV 4.1 PATHS /usr/local/lib NO_DEFAULT_PATH)
find_package(OpenCV 4.1)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

add_executable(mandelbrot src/main 
                          src/mandelbrot.cpp)
target_link_libraries(mandelbrot ${OpenCV_LIBRARIES})
target_link_libraries(mandelbrot pthread)

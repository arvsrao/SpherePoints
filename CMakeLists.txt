cmake_minimum_required(VERSION 2.6)
project(SPHERE_POINTS)
add_subdirectory(test) 

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin) 
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "-std=c++11")

ADD_EXECUTABLE( main main.cpp)
TARGET_LINK_LIBRARIES( main )

cmake_minimum_required(VERSION 3.5.1)
project(algorithms)

include(CTest)
set(CMAKE_CXX_FLAGS "-g3 -std=c++11")

include_directories("${PROJECT_SOURCE_DIR}/src")
add_subdirectory(src)


cmake_minimum_required(VERSION 3.5)
project(OpenCL-Query)

set(CMAKE_CXX_STANDARD 14) # C++14...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(THREADS_PREFER_PTHREAD ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCL REQUIRED)

add_executable(OpenCL-Query src/OpenCL-Query.cpp)
target_include_directories(OpenCL-Query PRIVATE ${OpenCL_INCLUDE_DIRS})
target_link_libraries(OpenCL-Query PRIVATE ${OpenCL_LIBRARIES})


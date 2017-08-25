cmake_minimum_required(VERSION 3.8)
project(ljus)

set(CMAKE_CXX_STANDARD 17)

include_directories (vendor/pistache/include)
add_subdirectory (vendor/pistache/src)
include_directories (vendor/pistache/src)

set(SOURCE_FILES ljus.cpp ljus.h ljus/http/LjusHandler.cpp ljus/http/LjusHandler.h)
add_executable(ljus ${SOURCE_FILES})
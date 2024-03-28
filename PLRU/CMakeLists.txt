cmake_minimum_required(VERSION 3.28.2)

project(PLRU)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(PLRU main.cpp plru.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug build")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Release build")
else()
    message("Unknown build type")
endif()




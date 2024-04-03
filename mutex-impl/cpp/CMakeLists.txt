cmake_minimum_required(VERSION 3.28.2)

project(MUTEX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# set CXX path
# set(CMAKE_CXX_COMPILER /opt/homebrew/opt/llvm/bin/clang++)
# set(CMAKE_C_COMPILER /opt/homebrew/opt/llvm/bin/clang)

add_executable(mutex test_mutex.cpp mutex.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic -g -O0")

# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#     message("Debug build")
# elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
#     message("Release build")
# else()
#     message("Unknown build type")
# endif()

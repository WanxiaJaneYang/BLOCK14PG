set(GOOGLETEST_VERSION "1.14.0")
set(CMAKE_OSX_ARCHITECTURES arm64)

cmake_minimum_required(VERSION 3.10)

project(BLOCK)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add your project source files
# add_executable(main src/main.cpp)

# Gather all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add executable or library using the source files
add_executable(main ${SOURCES})

# Google Test setup
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include)
add_subdirectory(googletest/googletest) 

# Add test executable
add_executable(runUnitTests tests/test_main.cpp)
target_link_libraries(runUnitTests gtest gtest_main)

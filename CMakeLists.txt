cmake_minimum_required(VERSION 3.10)

project(BLOCK)

# Add your project source files
add_executable(main src/main.cpp)

# Google Test setup
add_subdirectory(googletest/googletest) 
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include) # Including the right header path

# Add test executable
add_executable(runUnitTests tests/test_main.cpp)
target_link_libraries(runUnitTests gtest gtest_main)

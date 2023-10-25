set(GOOGLETEST_VERSION "1.14.0")
set(CMAKE_OSX_ARCHITECTURES arm64)

cmake_minimum_required(VERSION 3.10)

project(BLOCK)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add your project source files 

# Gather all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# Add executable or library using the source files
# add_executable(main ${SOURCES})

# Google Test setup
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include)
add_subdirectory(googletest/googletest) 

add_executable(integrationValidTests tests/integration/integrationValidTests.cpp 
tests/integration/integrationTestHelper.cpp 
tests/integration/integrationTestHelper.h
tests/integration/Chunk.cpp 
tests/integration/Chunk.h ${SOURCES})
target_compile_definitions(integrationValidTests PRIVATE TEST)
target_link_libraries(integrationValidTests gtest gtest_main)

add_executable(debug tests/integration/debug.cpp 
tests/integration/IntegrationTestHelper.cpp 
tests/integration/IntegrationTestHelper.h ${SOURCES})
target_compile_definitions(debug PRIVATE TEST)
target_link_libraries(debug gtest gtest_main)

set(GOOGLETEST_VERSION "1.14.0")
set(CMAKE_OSX_ARCHITECTURES arm64)

cmake_minimum_required(VERSION 3.10)

project(BLOCK)
set(CMAKE_CXX_STANDARD 17)
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

# add_executable(validInputTests tests/unit/readInput/validTests.cpp 
# tests/unit/readInput/InputTestHelper.cpp 
# tests/unit/readInput/InputTestHelper.h ${SOURCES})
# target_compile_definitions(validInputTests PRIVATE TEST)
# target_link_libraries(validInputTests gtest gtest_main)

# add_executable(invalidInputTests tests/unit/readInput/invalidTests.cpp 
# tests/unit/readInput/InputTestHelper.cpp 
# tests/unit/readInput/InputTestHelper.h ${SOURCES})
# target_compile_definitions(invalidInputTests PRIVATE TEST)
# target_link_libraries(invalidInputTests gtest gtest_main)

# add_executable(integrationValidTests tests/integration/integrationValidTests.cpp 
# tests/integration/integrationTestHelper.cpp 
# tests/integration/integrationTestHelper.h ${SOURCES})
# target_compile_definitions(integrationValidTests PRIVATE TEST)
# target_link_libraries(integrationValidTests gtest gtest_main)

add_executable(validCompressorPlaneTests tests/unit/compressor/planeCompress/validTests.cpp 
tests/unit/compressor/planeCompress/planeCompressTestHelper.cpp 
tests/unit/compressor/planeCompress/planeCompressTestHelper.h ${SOURCES})
target_compile_definitions(validCompressorPlaneTests PRIVATE TEST)
target_link_libraries(validCompressorPlaneTests gtest gtest_main)

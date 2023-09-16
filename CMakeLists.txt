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

add_executable(validCompressorBlockTests tests/unit/compressor/blockCompress/validTests.cpp 
tests/unit/compressor/blockCompress/blockCompressTestHelper.cpp 
tests/unit/compressor/blockCompress/blockCompressTestHelper.h ${SOURCES})
target_compile_definitions(validCompressorBlockTests PRIVATE TEST)
target_link_libraries(validCompressorBlockTests gtest gtest_main)

add_executable(transformToMapTest tests/unit/compressor/blockCompress/helperFunctionsTest/transformToMapTest.cpp
tests/unit/compressor/blockCompress/helperFunctionsTest/unitTestHelper.cpp 
tests/unit/compressor/blockCompress/helperFunctionsTest/unitTestHelpers.h ${SOURCES})
target_compile_definitions(transformToMapTest PRIVATE TEST)
target_link_libraries(transformToMapTest gtest gtest_main)

add_executable(minusCuboidTest tests/unit/compressor/blockCompress/helperFunctionsTest/minusCuboidTest.cpp
tests/unit/compressor/blockCompress/helperFunctionsTest/unitTestHelper.cpp 
tests/unit/compressor/blockCompress/helperFunctionsTest/unitTestHelpers.h ${SOURCES})
target_compile_definitions(minusCuboidTest PRIVATE TEST)
target_link_libraries(minusCuboidTest gtest gtest_main)

add_executable(findAllMatchedTest tests/unit/compressor/blockCompress/helperFunctionsTest/findAllMatchedTest.cpp
tests/unit/compressor/blockCompress/helperFunctionsTest/unitTestHelper.cpp 
tests/unit/compressor/blockCompress/helperFunctionsTest/unitTestHelpers.h ${SOURCES})
target_compile_definitions(findAllMatchedTest PRIVATE TEST)
target_link_libraries(findAllMatchedTest gtest gtest_main)

add_executable(blockCompressTest tests/unit/compressor/blockCompress/integrationSelfDebugging/BlockCompressTest.cpp
tests/unit/compressor/blockCompress/helperFunctionsTest/unitTestHelper.cpp 
tests/unit/compressor/blockCompress/helperFunctionsTest/unitTestHelpers.h ${SOURCES})
target_compile_definitions(blockCompressTest PRIVATE TEST)
target_link_libraries(blockCompressTest gtest gtest_main)
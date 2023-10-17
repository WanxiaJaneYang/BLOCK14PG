# src/CMakeLists.txt

# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Define the project and specify the required C++ standard
project(BLOCK)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# List source files
set(SOURCES 
    main.cpp 
    compressor/Compressor.cpp
    compressor/LineCompress.cpp
    compressor/PlaneCompress.cpp
    cores/Block.cpp 
    cores/Cuboid.cpp 
    cores/SafeInputTasks.cpp 
    cores/SafeOutputTasks.cpp 
    globals/globals.cpp 
    input/readInput.cpp
    input/Buffer.cpp
    multi-threads-handling/MultiThreadsHandler.cpp 
    output/output.cpp
)

# List header files (optional but can be useful in some IDEs like Visual Studio)
set(HEADERS 
    compressor/Compressor.h 
    cores/Block.h 
    cores/Cuboid.h 
    cores/SafeInputTasks.h 
    cores/SafeOutputTasks.h 
    globals/globals.h 
    input/readInput.h 
    input/Buffer.h
    multi-threads-handling/MultiThreadsHandler.h 
    multi-threads-handling/ThreadPool.h 
    output/output.h
)

# Add executable target
add_executable(BLOCK ${SOURCES} ${HEADERS})

# Compiler and linker flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU") # For GCC
    target_compile_options(BLOCK PRIVATE -m64)
    target_link_options(BLOCK PRIVATE -static -m64)
endif()



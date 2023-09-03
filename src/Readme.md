# BLOCK14PG Project

## Introduction

Welcome to the **BLOCK14PG** project repository. This document provides a brief overview of the project structure and instructions on how to build and run the source code.

## Project Structure

- `main.cpp`: The entry point for the application.
- `compressor/`: Contains source files related to compression operations.
- `cores/`: Core functionality and utility functions.
- `globals/`: Global variables and configurations.
- `input/`: Source files handling input operations.
- `multi-threads-handling/`: Multithreading handling related source files.
- `output/`: Source files handling output operations.

## Prerequisites

- CMake: Ensure you have CMake installed and available from the command line.
- Compiler: Make sure you have a C++ compiler installed that's compatible with your platform (e.g., MinGW for Windows or GCC for Linux).

## Building the Project

1. Navigate to the `src` directory:
    ```shell
    cd path/to/BLOCK14PG/src
    ```
2. Create a build directory (if it doesn't exist) and navigate into it:
```shell
    mkdir build
    cd build
```
3. Run CMake to configure and generate the build files. Use the appropriate generator for your build system. For Windows(MinGW), for example:
```
    cmake .. -G "MinGW Makefiles"
```
4. After configuring with CMake, compile the project. For Windows(MinGW), for example:
```
    mingw32-make
```
5. Once the build completes, the compiled executable should be located within the `build` directory.

## Running the Program

After building, you can run the program by navigating to the executable within the `build` directory and executing it.

Thank you for exploring the **BLOCK14PG** source code!




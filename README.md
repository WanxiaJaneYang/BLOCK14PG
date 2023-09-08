# BLOCK14PG

Brief project description or introduction here.

## File Structure

- **/src/**: 
  - **cores/**: Core classes used in the project.
  - **globals/**: Global variables utilized throughout the project.
  - **compression/**: Contains algorithms for compression.
  - **input/**: Functions related to input handling.
  - **output/**: Functions dedicated to output.
  - **multi-thread-handling/**: Handlers that utilize multi-threading capabilities.

- **/tests/**: 
  - **unit/**: Unit tests for various components.
    - **cores/**: Tests for core classes.
    - **globals/**: Tests related to global variables.
    - **compression/**: Tests for compression algorithms.
    ... (continue mirroring the `src/` structure)
  - **integration/**: Integration tests for the project.

## Tech Stack

- **Programming Language**: C++

## BLOCK14PG Project: Build and Test

### Introduction

Welcome to the **BLOCK14PG** project repository. This document provides instructions on how to build the main project source code and execute unit tests.

### Prerequisites

- **CMake**: Ensure you have CMake installed and available from the command line.
    - **macOS**: 
        ```shell
        brew install cmake
        ```
    - **Windows**: Download the CMake installer from the [official website](https://cmake.org/download/) and follow the installation instructions. Alternatively, if you have Chocolatey installed:
        ```shell
        choco install cmake
        ```

- **Compiler**: Ensure a C++ compiler is installed suitable for your platform, e.g., MinGW for Windows or GCC for Linux.

- **Google Test Framework**: This is essential for our unit tests.
    ```
    git clone https://github.com/google/googletest.git
    ```
    - If the folder is empty after a pull, ensure to run the above command.
    - Add "${workspaceFolder}/googletest/googletest/include" to your environment configuration.

### Building the Main Project

1. Navigate to the `src` directory:
    ```shell
    cd path/to/BLOCK14PG/src
    ```

2. Create a build directory (if it doesn't exist) and navigate into it:
    ```shell
    mkdir build
    cd build
    ```

3. Configure the project using CMake. Adapt the generator as per your build system:
    ```shell
    cmake .. -G "MinGW Makefiles"  # For Windows with MinGW
    ```

4. Compile the project:
    ```shell
    mingw32-make   # For Windows with MinGW
    ```

5. The compiled executable can be found within the `build` directory. Navigate there to run the program.

### Setting Up and Running Unit Tests

1. Make sure the prerequisites mentioned above are met.

2. Add your test case in the `valid_test_cases` folder or `invalid_test_cases` folder.
    - Ensure you follow the naming convention.
    - Place the expected result text file in the same folder. Keep the tag table in alphabetical order and add a blank line before each Block title.

3. For Unit Test Contributors:
    - Edit the project's root `CMakeLists.txt` to include your test executable:
        ```shell
        # Add test executable
        add_executable(runUnitTests tests/test_main.cpp ${source})
        target_link_libraries(runUnitTests gtest gtest_main)
        ```

    - Create or modify `tests/test_main.cpp` or another preferred file name.
    - Navigate to the `googletest` directory, then to `build`. If the `build` directory doesn't exist, create it:
        ```shell
        cd googletest
        mkdir -p build
        cd build
        ```

    - Configure the project using CMake:
        ```shell
        cmake ..
        ```

    - Compile the tests:
        ```shell
        make
        ```

    - Run the tests:
        ```shell
        ./runUnitTests
        ```

## Static Code Analysis - Cppcheck

We've integrated Cppcheck for static code analysis to maintain code quality. Before committing any changes, it's recommended to run Cppcheck locally to spot any potential issues.

### How to run Cppcheck locally:

1. Install Cppcheck on your machine. For most platforms, you can find installation instructions on the [official Cppcheck website](http://cppcheck.sourceforge.net/).

2. Navigate to your project directory in the terminal or command prompt.

3. Use the following command to run Cppcheck:
   - For `src/` with C++11 standard: 
     ```bash
     cppcheck --enable=all --std=c++11 src/
     ```
   - For `tests/` with C++17 standard: 
     ```bash
     cppcheck --enable=all --std=c++17 tests/
     ```

Make sure you've resolved any warnings or errors flagged by Cppcheck before making a commit.

### Notes:

- If you're a first-time user, the tool might report some false positives or suggest micro-optimizations. Focus on genuine issues or bugs it highlights.

- In case you encounter a lot of "missing include" notifications, you can add `--suppress=missingIncludeSystem` to the command to suppress them. However, these are typically informational and can be ignored.

## Continuous Integration (CI) and Testing

In **BLOCK14PG**, we use GitHub Actions to ensure that our codebase remains consistent and reliable. This helps us detect and fix issues early in the development process, improving the overall quality of our software.

### CI Configuration

Our CI is configured to test the code in the following environments:

- **macOS**: Using the `clang++` compiler.
- **Windows**: Using the `g++` compiler.

To see the CI status for recent commits, navigate to the `Actions` tab in our GitHub repository.

### Collaborator Guidelines

For collaborators:

- Ensure your code builds successfully and tests pass both locally and on the CI before merging changes.
- Follow our coding standards and best practices.
- Before merging, ensure Cppcheck static analysis does not return warnings or errors.

### Feedback and Troubleshooting

If you encounter an issue or have suggestions, please discuss it with the team or mention it in our internal communication channels.

To be added: "Getting Started", "Installation", "Usage", etc.


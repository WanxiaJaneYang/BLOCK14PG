1. brew install cmake  
2. install VS code extention 'CMake tools'  
3. git clone git clone https://github.com/google/googletest.git
4. Add CMakeLists.txt at root  
```  
    set(GOOGLETEST_VERSION "1.14.0")
    cmake_minimum_required(VERSION 3.10)

    project(BLOCK)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    # Add your project source files
    add_executable(main src/input/readInput.cpp)

    # Google Test setup
    add_subdirectory(googletest/googletest) 
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include)

    # Add test executable
    add_executable(runUnitTests tests/test_main.cpp)
    target_link_libraries(runUnitTests gtest gtest_main)

```
7. read googletest/README.md
8. create file tests/test_main.cpp
9. paste a demo test
10. cd googletest
11. mkdir build
12. cd build
13. cmake ..
14. make
15. run ./runUnitTests

  #### For developer to test:   
1. brew install cmake  // different command for windows to install cmake
2. install VS code extention 'CMake tools' via VScode GUI
   
3. git clone https://github.com/google/googletest.git if the folder is still empty after pull  
4. add "${workspaceFolder}/googletest/googletest/include" to env config
5. run:
  ```  
cd googletest/build  // mkdir build if no 'build' folder
cmake ../..          // only needed when first loading 
                     // and after adding new cpp/h file
make                 // any time after editing existing cpp/h file
./validInputTests 
./invalidInputTests  // optional
  ``` 
 #### For test cases worker:   
1. put your test case in valid_test_cases folder or invalid_test_cases folder  
2. keep the name convention  
3. put your expected result text file in the same folder, keep tag table in alphabetical order, blank line before Block title      
          
#### for unit testor to collaborate:             
1. brew install cmake  // different command for windows to install cmake
2. install VS code extention 'CMake tools' via VScode GUI
3. git clone https://github.com/google/googletest.git if the folder is empty
4. add "${workspaceFolder}/googletest/googletest/include" to env config
5. Add your executeable test file into root->CMakeLists.txt  
```  
    # Add test executable
    add_executable(runUnitTests tests/test_main.cpp ${source}) #here
    target_link_libraries(runUnitTests gtest gtest_main) #here

```
7. read googletest/README.md
8. create file tests/test_main.cpp or other name
9. paste a demo test
10. cd googletest
11. mkdir build
12. cd build
13. cmake ..
14. make 
15. run ./runUnitTests

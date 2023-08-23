  #### For developer to test: run  
  ```  
cd build  
./inputUnitTests
  ``` 
    
      
        
          
#### for unit testor to collaborate:             
1. brew install cmake  
2. install VS code extention 'CMake tools'  
3. git clone git clone https://github.com/google/googletest.git if folder is empty
4. Add your executeable test file into root->CMakeLists.txt  
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

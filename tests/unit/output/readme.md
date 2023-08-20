#### for mac developer:  
```  
brew install boost  
```  
```  
clang++ -std=c++11 ./outputTest.cpp ../../../src/output/output.cpp ../../../src/globals/globals.cpp ../../../src/cores/Cuboid.cpp ../../../src/cores/SafeOutputTasks.cpp ../../../src/cores/SafeInputTasks.cpp ../../../src/cores/Block.cpp -I $(brew --prefix boost)/include -I/Users/kaini/Documents/SEP/BLOCK14PG/src/output/ -L $(brew --prefix boost)/lib -lboost_unit_test_framework -o test_output_program  
```  

Replace the path to the boost library with your own path.  
and the path to your repository.  
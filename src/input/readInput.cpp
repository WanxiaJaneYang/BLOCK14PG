#include "readInput.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

void readInput()
{
    // Read input file using the file name stored in GlobalVars::inputFileName
    // and store the data in GlobalVars::processTasks

    GlobalVars::inputFileName = "./input.txt";

    std::ifstream file(GlobalVars::inputFileName);

    if (!file)
    {
        std::cerr << "Unable to open file: " << GlobalVars::inputFileName << std::endl;
        return;                                                         
    }

    std::string line;

    while (std::getline(file, line))
    {
        
        std::cout << line << std::endl;
    }

    file.close();
}

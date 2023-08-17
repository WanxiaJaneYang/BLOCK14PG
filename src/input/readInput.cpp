#include "readInput.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

void readInput()
{
    // Read input file using the file name stored in GlobalVars::inputFileName
    // and store the data in GlobalVars::processTasks

    GlobalVars::inputFileName = "./input/input.txt";

    std::ifstream file(GlobalVars::inputFileName);

    if (!file)
    {
        std::cerr << "Unable to open file: " << GlobalVars::inputFileName << std::endl;
        return;                                                         
    }

    std::string line;

    // get first line
    std::getline(file, line);
    std::istringstream iss(line);
    int big_width,big_height,big_depth;
    char comma;
    // collect size parameters
    iss >> big_width >> comma >> big_height >> comma >> big_depth >> comma >> GlobalVars::width >> comma >> GlobalVars::height >> comma >> GlobalVars::depth;
    
    // get labels pairs lines
    while (std::getline(file, line))
    {
        if (line.find(',') == std::string::npos) break;
        std::istringstream ss(line);
        char key;
        std::string value;
        ss >> key >> comma;
        std::getline(ss, value, ',');
        GlobalVars::tagTable[key] = value;
    }

    // for testing print
    // std::cout << big_width << " "
    //           << big_height << " "
    //           << big_depth << " "
    //           << GlobalVars::width << " "
    //           << GlobalVars::height << " "
    //           << GlobalVars::depth << std::endl;

    // for (const auto &pair : GlobalVars::tagTable)
    // {
    //     std::cout << pair.first << " -> " << pair.second << std::endl;
    // }

    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }

    file.close();
}

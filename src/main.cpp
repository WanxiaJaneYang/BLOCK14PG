#include "multi-threads-handling/MultiThreadsHandler.h"
#include "globals/globals.h"
#include <iostream>
#include <fstream>
#include <string>

int main()
{
    GlobalVars::inputFileName = "input.txt";
    GlobalVars::outputFileName = "output.txt";

    // read the input from iostream and write it to input.txt
    std::ofstream outFile("input/input.txt");

    if (!outFile.is_open())
    {
        std::cerr << "Failed to open output file." << std::endl;
        return 1;
    }

    std::string line;
    while (true)
    {
        std::getline(std::cin, line); // Read a line from standard input

        // If the input stream hits EOF or another error occurs
        if (!std::cin)
        {
            // Check for EOF (end-of-file)
            if (std::cin.eof())
            {
                break; // Exit the loop if EOF is reached
            }

            // Handle other errors
            std::cerr << "Error reading from standard input." << std::endl;
            return 2;
        }

        outFile << line << std::endl; // Write the line to the file
    }

    outFile.close();

    // call the threads to read, compress and write
    startThreads();

    // read the output from output.txt and write it to iostream
    std::ifstream inFile("output.txt");

    if (!inFile.is_open())
    {
        std::cerr << "Failed to open ouput file." << std::endl;
        return 1;
    }

    while (std::getline(inFile, line))
    {                                   // Read a line from the file
        std::cout << line << std::endl; // Write the line to standard output
    }

    // Check for reading errors other than EOF
    if (!inFile.eof())
    {
        std::cerr << "Error reading from the file." << std::endl;
        return 2;
    }

    inFile.close();
    return 0;
}
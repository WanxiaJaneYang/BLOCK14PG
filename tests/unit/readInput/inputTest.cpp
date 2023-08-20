#include "../../../src/input/readInput.h"
#include "../../../src/globals/globals.h"
#include <iostream>

int main()
{
    // read input
	std::cout << "Reading input file..." << std::endl;
    readInput();
    std::cout << "Finished reading input file." << std::endl;
    
    // print all global vars
	// print parent size
	std::cout << GlobalVars::width << ",";
	std::cout << GlobalVars::height << ",";
	std::cout << GlobalVars::depth << std::endl;

	// print labels
	for (const auto& pair : GlobalVars::tagTable) {
        std::cout << pair.first << "," << pair.second << std::endl;
    }

	std::cout << std::endl;

	// print process tasks
    GlobalVars::processTasks.printTasks();

    return 0;
}
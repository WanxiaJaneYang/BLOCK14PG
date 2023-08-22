#include "input/readInput.h"
#include <iostream>

int main() {
    try {
        readInput();
        std::cout << "Input invoked successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error occurred while reading input: " << e.what() << std::endl;
        return 1; // Return with error code
    }
    return 0; // Successful exit
}

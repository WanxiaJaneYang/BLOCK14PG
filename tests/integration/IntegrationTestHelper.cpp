#include "IntegrationTestHelper.h"
#include <experimental/filesystem>

// Utility function to get all input files from a directory
std::vector<std::string> listInputFiles(const std::string& directory) {
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        // if (entry.path().extension() == ".txt" && entry.path().string().find("_case.txt") != std::string::npos) {

        if (entry.path().extension() == ".csv" && entry.path().string().find("_case.csv") != std::string::npos) {
            std::cout << entry.path().string() << std::endl;
            files.push_back(entry.path().string());
        }
    }
    return files;
}

std::istringstream simulateInputStream(const std::string& filePath) {
    // Read the content of the file into an istringstream
    std::ifstream inFile(filePath);

    // simulate input stream
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    return std::istringstream(buffer.str());
}

std::vector<std::string> sortedLinesFromStream(std::istream& stream) {
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(stream, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        lines.push_back(line);
    }

    std::sort(lines.begin(), lines.end());
    
    return lines;
}







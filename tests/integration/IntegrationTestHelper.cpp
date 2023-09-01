#include "IntegrationTestHelper.h"

// Utility function to get all input files from a directory
std::vector<std::string> listInputFiles(const std::string& directory) {
    std::vector<std::string> files;
    for (const auto& entry : std::__fs::filesystem::directory_iterator(directory)) {
        // if (entry.path().extension() == ".txt" && entry.path().string().find("_case.txt") != std::string::npos) {

        if (entry.path().extension() == ".csv" && entry.path().string().find("_case.csv") != std::string::npos) {
            std::cout << entry.path().string() << std::endl;
            files.push_back(entry.path().string());
        }
    }
    return files;
}


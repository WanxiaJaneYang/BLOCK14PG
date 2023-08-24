#include "InputTestHelper.h"

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

// Utility function to write tasks into a string
std::string writeContentOfTasks(SafeInputTasks& tasks) {
    std::ostringstream oss;
    for (int i = 0; i < tasks.size(); ++i) {
        Block& block = tasks.getFromIndex(i);
        // Assuming Block has a method that returns a string representation
        oss << "\n\n" << "Block" << (i + 1) << writeContentOfBlock(block);
    }
    return oss.str();
}

// Utility function to write the block into a string
std::string writeContentOfBlock(Block& block)
{
    std::ostringstream oss;
    auto data = block.getData();  // Fetch the data using the public getData() method
    
    for (const auto &outer : data){
        oss << "\n";
        for (const auto &inner : outer){
            oss << "\n";
            for (char c : inner){
                oss << c;
            }
        }
    }
    return oss.str();
}

std::string writeReadContent(){

    // Convert the data stored into a string
    std::ostringstream oss;
    oss << GlobalVars::width << ",";
    oss << GlobalVars::height << ",";
    oss << GlobalVars::depth ;

    // write labels into the string
    for (const auto& pair : GlobalVars::tagTable) {
        oss << "\n" << pair.first << "," << pair.second;
    }

    // Add blocks in tasks to the string
    oss << writeContentOfTasks(GlobalVars::processTasks);

    clearTasks(GlobalVars::processTasks);// important for bulk tests

    return oss.str();
}

//clears the tasks vector
void clearTasks(SafeInputTasks& tasks)
{
    // tasks.tasks.clear();
    Block dummy;
    while (tasks.pop(dummy));
}
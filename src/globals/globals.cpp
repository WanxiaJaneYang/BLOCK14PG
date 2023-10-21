#include "globals.h"

// global variables
namespace GlobalVars
{
    std::string inputFileName;
    std::string outputFileName;
    std::map<char, std::string> tagTable;
    SafeInputTasks processTasks;
    SafeOutputTasks outputTasks;
    int width;
    int height;
    int depth;
    std::mutex coutMutex;
}
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
    std::mutex bufferMtx;
    std::map<int, std::deque<std::deque<Cuboid>>> intermediateBuffer;
    int nextExpectedBlockID = 0;
    std::atomic<bool> newBlockCompressedSingnal(false);

}
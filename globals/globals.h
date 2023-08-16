#include <string>
#include <vector>
#include <map>

#include "../cores/Block.h"
#include "../cores/Cuboid.h"
#include "../cores/SafeInputTasks.h"
#include "../cores/SafeOutputTasks.h"

#ifndef GLOBALS_H
#define GLOBALS_H

namespace GlobalVars
{
    extern std::string inputFileName;
    extern std::string outputFileName;
    extern std::map<char, std::string> tagTable;
    extern SafeInputTasks processTasks;
    extern SafeOutputTasks outputTasks;
    extern int width;
    extern int height;
    extern int depth;
}
#endif
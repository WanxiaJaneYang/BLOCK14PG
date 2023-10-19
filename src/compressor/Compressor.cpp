#include "Compressor.h"
#include "../globals/globals.h"
#include "../cores/SafeInputTasks.h"
#include "../cores/SafeOutputTasks.h"
#include <deque>
#include <mutex>

std::mutex tasksMutex;

void compress()
{
    {
        std::lock_guard<std::mutex> lock(tasksMutex); // protect line and plane function call

        while (GlobalVars::processTasks.size() > 0) // also being protected as there's a time gap between size>0 & pop
        {
            Block block;
            GlobalVars::processTasks.pop(block);

            // compress the block, first compress the line
            std::deque<std::deque<std::deque<Cuboid>>> lineCompressed = lineCompress(block);
            // read line by line and compress them into rectangles
            planeCompress(lineCompressed);
        }
    }
}

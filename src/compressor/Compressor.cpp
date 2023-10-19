#include "Compressor.h"
#include "../globals/globals.h"
#include "../cores/SafeInputTasks.h"
#include "../cores/SafeOutputTasks.h"
#include <deque>
#include <mutex>

std::mutex tasksMutex;

void compress()
{
    while (true) // Use an infinite loop since we're going to control the exit within the loop
    {
        Block block;

        //critical section
        {
            std::lock_guard<std::mutex> lock(tasksMutex);
            // Exit the function if there's no more tasks to process
            if (GlobalVars::processTasks.size() == 0)
                break;

            GlobalVars::processTasks.pop(block);
        }

        // These functions are outside the lock, allowing concurrent execution
        std::deque<std::deque<std::deque<Cuboid>>> lineCompressed = lineCompress(block);
        planeCompress(lineCompressed);
    }
}

// void compress()
// {
//     while (GlobalVars::processTasks.size() > 0) //  there's a time gap between size>0 & pop
//     {
//         Block block;
//         GlobalVars::processTasks.pop(block);

//         // compress the block, first compress the line
//         std::deque<std::deque<std::deque<Cuboid>>> lineCompressed = lineCompress(block);
//         // read line by line and compress them into rectangles
//         planeCompress(lineCompressed);
//     }
// }

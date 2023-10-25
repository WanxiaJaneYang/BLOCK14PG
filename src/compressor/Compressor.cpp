#include "Compressor.h"
#include "../globals/globals.h"
#include "../cores/SafeInputTasks.h"
#include "../cores/SafeOutputTasks.h"
#include <deque>
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>

void compress()
{
    std::thread::id this_id = std::this_thread::get_id();

    while (true) // Use an infinite loop since we're going to control the exit within the loop
    {
        Block block;
        bool hasBlock = GlobalVars::processTasks.pop(block);

        if (!hasBlock)
        {
            break;
        }
        // {
        //     std::lock_guard<std::mutex> lock(GlobalVars::coutMutex);
        //     std::cout << "Started Compression of Block: " << block.id << "  Compressing thread ID: " << this_id << std::endl;
        // }
        std::deque<std::deque<std::deque<Cuboid>>> lineCompressed = lineCompress(block);
        std::deque<std::deque<Cuboid>> planeCompressed = planeCompress(lineCompressed);
        {
            std::lock_guard<std::mutex> lock(GlobalVars::bufferMtx);
            GlobalVars::intermediateBuffer[block.id] = planeCompressed;
            // {
            //     std::lock_guard<std::mutex> lock(GlobalVars::coutMutex);
            //     std::cout << "Finished Compression of Block: " << block.id << std::endl;
            // }
            GlobalVars::newBlockCompressedSingnal.store(true);
        }
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

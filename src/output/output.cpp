#include "output.h"
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

// print the Cuboid information in the required output format
void output()
{
    // std::cout << "output being called" << std::endl;
    std::deque<std::deque<Cuboid>> cuboidsGroup;
    while (true)
    {
        {
            std::lock_guard<std::mutex> lock(GlobalVars::bufferMtx);
            auto it = GlobalVars::intermediateBuffer.find(GlobalVars::nextExpectedBlockID);
            // if found the in-order block, push it to output and increment nextExpectedBlockID

            if (it == GlobalVars::intermediateBuffer.end())
            {
                // {
                //     std::lock_guard<std::mutex> lock(GlobalVars::coutMutex);
                //     std::cout << "!!!!!!!! not found nextExpectedBlockID: " << GlobalVars::nextExpectedBlockID << std::endl;
                // }
                break;
            }

            // {
            //     std::lock_guard<std::mutex> lock(GlobalVars::coutMutex);
            //     std::cout << "found nextExpectedBlockID: " << GlobalVars::nextExpectedBlockID << std::endl;
            // }
            cuboidsGroup = it->second;

            GlobalVars::intermediateBuffer.erase(it);
        }
        GlobalVars::nextExpectedBlockID++;

        for (const auto &cuboids : cuboidsGroup)
        {
            for (const auto &cuboid : cuboids)
            {
                int positionX = cuboid.blockX + cuboid.cuboidX;
                int positionY = cuboid.blockY + cuboid.cuboidY;
                int positionZ = cuboid.blockZ + cuboid.cuboidZ;
                int sizeX = cuboid.width;
                int sizeY = cuboid.height;
                int sizeZ = cuboid.depth;
                std::string label = GlobalVars::tagTable.at(cuboid.tag);

                // only one thread at a time can output, no contention
                //  {
                //      std::lock_guard<std::mutex> coutLock(GlobalVars::coutMutex);
                std::cout << positionX << "," << positionY << "," << positionZ << ","
                          << sizeX << "," << sizeY << "," << sizeZ << "," << label << std::endl;
                // }
            }
        }
    }
}

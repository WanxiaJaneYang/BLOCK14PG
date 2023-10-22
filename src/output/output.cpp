#include "output.h"
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

// print the Cuboid information in the required output format
void output()
{
    // get Cuboid from GlobalVars::outputTasks
    Cuboid cuboid;
    while (true)
    {

        bool outputCuboid = GlobalVars::outputTasks.pop(cuboid);
        if (!outputCuboid)
        {
            // sleep for 1 ms to avoid frequet exit and restart
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            outputCuboid = GlobalVars::outputTasks.pop(cuboid);
            if (!outputCuboid)
            {
                break;
            }
        }

        //  calculate correct block position
        int positionX = cuboid.blockX + cuboid.cuboidX;
        int positionY = cuboid.blockY + cuboid.cuboidY;
        int positionZ = cuboid.blockZ + cuboid.cuboidZ;
        int sizeX = cuboid.width;
        int sizeY = cuboid.height;
        int sizeZ = cuboid.depth;
        std::string label = GlobalVars::tagTable.at(cuboid.tag);
        //  print out the block position, block size and accurate label
        // {
        //     std::lock_guard<std::mutex> coutLock(GlobalVars::coutMutex);
            std::cout << positionX << "," << positionY << "," << positionZ << "," << sizeX << "," << sizeY << "," << sizeZ << "," << label << std::endl;
        // }
    }
}
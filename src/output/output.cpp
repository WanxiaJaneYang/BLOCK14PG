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
        bool outputDeque = GlobalVars::outputTasks.pop(cuboidsGroup);
            // std::cout << "poped" << outputDeque << std::endl;

        if (!outputDeque)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            outputDeque = GlobalVars::outputTasks.pop(cuboidsGroup);
            if (!outputDeque)
            {
                break;
            }
        }

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
                // {
                //     std::lock_guard<std::mutex> coutLock(GlobalVars::coutMutex);
                std::cout << positionX << "," << positionY << "," << positionZ << ","
                          << sizeX << "," << sizeY << "," << sizeZ << "," << label << std::endl;
                // }
            }
        }
    }
}

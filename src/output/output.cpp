#include "output.h"
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

// print the Cuboid information in the required output format
void output()
{
    // std::cout << "output being called" << std::endl;
    while (true)
    {
        auto item = GlobalVars::blockStatus.find(GlobalVars::nextExpectedBlockID);

        if (item == GlobalVars::blockStatus.end())
        {
            // in case of too frequent checking
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            break;
        }
        char status;
        status = item->second;
        {
            std::lock_guard<std::mutex> lock(GlobalVars::bufferMtx);
            auto it = GlobalVars::intermediateBuffer.find(GlobalVars::nextExpectedBlockID);
            // if found the in-order block, push it to output and increment nextExpectedBlockID
            while (it != GlobalVars::intermediateBuffer.end())
            {
                // {
                //     std::lock_guard<std::mutex> lock(GlobalVars::coutMutex);
                //     std::cout << "found nextExpectedBlockID: " << GlobalVars::nextExpectedBlockID << std::endl;
                // }

                int positionX = it->second.blockX + it->second.cuboidX;
                int positionY = it->second.blockY + it->second.cuboidY;
                int positionZ = it->second.blockZ + it->second.cuboidZ;
                int sizeX = it->second.width;
                int sizeY = it->second.height;
                int sizeZ = it->second.depth;
                std::string label = GlobalVars::tagTable.at(it->second.tag);

                // only one thread at a time can output, no contention
                //  {
                //      std::lock_guard<std::mutex> coutLock(GlobalVars::coutMutex);
                std::cout << positionX << "," << positionY << "," << positionZ << ","
                          << sizeX << "," << sizeY << "," << sizeZ << "," << label << std::endl;
                // }

                GlobalVars::intermediateBuffer.erase(it);
                it = GlobalVars::intermediateBuffer.find(GlobalVars::nextExpectedBlockID);
            }
        }

        if (status == 'f')
        {
            GlobalVars::nextExpectedBlockID++;
        }
    }
}

#include "output.h"
#include <iostream>

// print the Cuboid information in the required output format
void output()
{
    // get Cuboid from GlobalVars::outputTasks
    Cuboid cuboid;
    bool outputCuboid = GlobalVars::outputTasks.pop(cuboid);
    while (outputCuboid)
    {
        //  calculate correct block position
        int positionX = cuboid.blockX + cuboid.cuboidX;
        int positionY = cuboid.blockY + cuboid.cuboidY;
        int positionZ = cuboid.blockZ + cuboid.cuboidZ;
        int sizeX = cuboid.width;
        int sizeY = cuboid.height;
        int sizeZ = cuboid.depth;
        std::string label = GlobalVars::tagTable.at(cuboid.tag);
        //  print out the block position, block size and accurate label
        std::cout << positionX << ", " << positionY << ", " << positionZ << ", " << sizeX << ", " << sizeY << ", " << sizeZ << "," << label << std::endl;
        outputCuboid = GlobalVars::outputTasks.pop(cuboid);
    }
}
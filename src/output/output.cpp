#include "output.h"
#include <fstream>
#include <iostream>

void output()
{
    // create and open file GlobalVars::outputFileName
    std::ofstream outputFile(GlobalVars::outputFileName);
    // get Cuboid from GlobalVars::outputTasks
    Cuboid cuboid;
    bool outputCuboid = GlobalVars::outputTasks.pop(cuboid);
    //  get the correct output format
    while (outputCuboid)
    {
        int positionX = cuboid.blockX + cuboid.cuboidX;
        int positionY = cuboid.blockY + cuboid.cuboidY;
        int positionZ = cuboid.blockZ + cuboid.cuboidZ;
        int sizeX = cuboid.width;
        int sizeY = cuboid.height;
        int sizeZ = cuboid.depth;
        std::string label = GlobalVars::tagTable.at(cuboid.tag);
        //  Write into output file
        std::cout << positionX << ", " << positionY << ", " << positionZ << ", " << sizeX << ", " << sizeY << ", " << sizeZ << ", " << label << std::endl;
        outputFile << positionX << "," << positionY << "," << positionZ << "," << sizeX << "," << sizeY << "," << sizeZ << "," << label << std::endl;
        outputCuboid = GlobalVars::outputTasks.pop(cuboid);
    }
    outputFile.close();
}

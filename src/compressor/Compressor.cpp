#include "Compressor.h"
#include "../globals/globals.h"
#include "../cores/SafeInputTasks.h"
#include "../cores/SafeOutputTasks.h"
#include <deque>

void compress()
{
    while (GlobalVars::processTasks.size() > 0)
    {
        Block block;
        GlobalVars::processTasks.pop(block);

        // compress the block, first compress the line
        std::deque<std::deque<std::deque<Cuboid>>> lineCompressed = lineCompress(block);
        // read line by line and compress them into rectangles
        std::deque<std::deque<Cuboid>> planeCompressed = planeCompress(lineCompressed);
        // read plane by plane and compress them into cuboids
        blockCompress(planeCompressed);
    }
}
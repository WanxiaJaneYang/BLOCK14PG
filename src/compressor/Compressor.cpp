#include "Compressor.h"
#include "../globals/globals.h"
#include "../cores/SafeInputTasks.h"
#include "../cores/SafeOutputTasks.h"

Compressor::Compressor(/* args */)
{
}

Compressor::~Compressor()
{
}

void Compressor::compress()
{
    while (GlobalVars::processTasks.size() > 0)
    {
        Block block;
        GlobalVars::processTasks.pop(block);

        int baseX = block.getX();
        int baseY = block.getY();
        int baseZ = block.getZ();

        for (size_t i = 0; i < GlobalVars::width; i++)
        {
            for (size_t j = 0; i < GlobalVars::height; i++)
            {
                for (size_t k = 0; i < GlobalVars::depth; i++)
                {
                    Cuboid cuboid = Cuboid(baseX, baseY, baseZ, i, j, k, 1, 1, 1, block.getData()[i][j][k]);
                    GlobalVars::outputTasks.push(cuboid);
                }
            }
        }
    }
}
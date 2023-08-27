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

        // int start, end;

        for (size_t z = 0; z < GlobalVars::depth; z++)
        {
            for (size_t y = 0; y < GlobalVars::height; y++)
            {
                // start = 0;
                for (size_t x = 0; x < GlobalVars::width; x++)
                {
                    // if (x > 0)
                    // {
                    //     if (block.getData()[z][y][x] != block.getData()[z][y][x - 1])
                    //     {
                    //         end = x - 1;
                    //         Cuboid cuboid = Cuboid(baseX, baseY, baseZ, start, y, z, end - start + 1, 1, 1, block.getData()[z][y][x - 1]);
                    //         GlobalVars::outputTasks.push(cuboid);
                    //         start = x;
                    //     }

                    //     if (x == GlobalVars::width - 1)
                    //     {
                    //         end = x;
                    //         Cuboid cuboid = Cuboid(baseX, baseY, baseZ, start, y, z, end - start + 1, 1, 1, block.getData()[z][y][x]);
                    //         GlobalVars::outputTasks.push(cuboid);
                    //     }
                    // }
                    Cuboid cuboid = Cuboid(baseX, baseY, baseZ, x, y, z, 1, 1, 1, block.getData()[z][y][x]);
                    GlobalVars::outputTasks.push(cuboid);
                }
            }
        }
    }
}
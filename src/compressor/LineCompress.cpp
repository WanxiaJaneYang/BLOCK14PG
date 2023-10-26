#include "Compressor.h"
#include <deque>
#include "../cores/Cuboid.h"
#include "../globals/globals.h"
#include <iostream>
// std::deque<std::deque<std::deque<Cuboid>>>
void lineCompress(Block &block, int thread)
{
    std::deque<std::deque<std::deque<Cuboid>>> result;
    int baseX = block.getX();
    int baseY = block.getY();
    int baseZ = block.getZ();
    int blockId = block.getId();
    int depth;
    int Z;
    if (thread == 1)
    {
        Z=0;
        depth = GlobalVars::depth / 2;
    }
    else
    {
        Z = GlobalVars::depth - GlobalVars::depth / 2;
        depth = GlobalVars::depth;
    }
    int start, end;
    for (size_t z = Z; z < depth; z++)
    {
        std::deque<std::deque<Cuboid>> plane;
        for (size_t y = 0; y < GlobalVars::height; y++)
        {
            // {
            //     std::lock_guard<std::mutex> lock(GlobalVars::coutMutex);
            //     std::cout << "Started lineCompression of Line: " << y << std::endl;
            // }
            std::deque<Cuboid> line;
            // reset the start point
            start = 0;
            for (size_t x = 0; x < GlobalVars::width; x++)
            {
                if (x > 0)
                {
                    // the color of the current point is differet from the previous one
                    if (block.getData()[z][y][x] != block.getData()[z][y][x - 1])
                    {
                        // push the previous cuboid into the line
                        end = x - 1;
                        Cuboid cuboid = Cuboid(baseX, baseY, baseZ, start, y, z, end - start + 1, 1, 1, block.getData()[z][y][x - 1]);
                        // line.push_back(cuboid);
                        {
                            std::lock_guard<std::mutex> lock(GlobalVars::bufferMtx);
                            GlobalVars::intermediateBuffer.insert(std::make_pair(blockId, cuboid));
                        }
                        // reset the start point
                        start = x;
                    }

                    // the current point is the last point of the line
                    if (x == GlobalVars::width - 1)
                    {
                        // push the previous cuboid into the line
                        end = x;
                        Cuboid cuboid = Cuboid(baseX, baseY, baseZ, start, y, z, end - start + 1, 1, 1, block.getData()[z][y][x]);
                        // line.push_back(cuboid);
                        {
                            std::lock_guard<std::mutex> lock(GlobalVars::bufferMtx);
                            GlobalVars::intermediateBuffer.insert(std::make_pair(blockId, cuboid));
                        }
                    }
                }
            }
            // plane.push_back(line);
        }
        // result.push_back(plane);
    }

    // return result;
}

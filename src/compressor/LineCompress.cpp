#include "Compressor.h"
#include <deque>
#include "../cores/Cuboid.h"
#include "../globals/globals.h"

std::deque<std::deque<std::deque<Cuboid>>> lineCompress(Block &block)
{
    std::deque<std::deque<std::deque<Cuboid>>> result;
    int baseX = block.getX();
    int baseY = block.getY();
    int baseZ = block.getZ();

    int start, end;
    for (size_t z = 0; z < GlobalVars::depth; z++)
    {
        std::deque<std::deque<Cuboid>> plane;
        for (size_t y = 0; y < GlobalVars::height; y++)
        {
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
                        line.push_back(cuboid);
                        // reset the start point
                        start = x;
                    }

                    // the current point is the last point of the line
                    if (x == GlobalVars::width - 1)
                    {
                        // push the previous cuboid into the line
                        end = x;
                        Cuboid cuboid = Cuboid(baseX, baseY, baseZ, start, y, z, end - start + 1, 1, 1, block.getData()[z][y][x]);
                        line.push_back(cuboid);
                    }
                }
            }
            plane.push_back(line);
        }
        result.push_back(plane);
    }

    return result;
}
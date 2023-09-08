#include "Compressor.h"
#include <deque>
#include "../globals/globals.h"
#include "../cores/SafeOutputTasks.h"
#include <algorithm>

/*compress the planes into cuboid and push them into output tasks*/
void blockCompress(std::deque<std::deque<Cuboid>> &planes)
{
    std::deque<Cuboid> cuboidsToBeMerged;
    // read plane by plane
    for (size_t z = 0; z < GlobalVars::depth; z++)
    {
        // similar logic as planeCompress
        if (z == 0)
        {
            cuboidsToBeMerged = planes[z];
            sortCuboids(cuboidsToBeMerged);
        }
        else
        {
            std::deque<Cuboid> currentPlane = planes[z];
            sortCuboids(currentPlane);
            while (cuboidsToBeMerged.size() != 0 && currentPlane.size() != 0)
            {
                // get the first cuboid of the two planes
                Cuboid cuboidToBeMerged = cuboidsToBeMerged.front();
                Cuboid current = currentPlane.front();

                // check the coordinates of the two cuboid
                // if the two cuboids's baseX, baseY are the same
                if (cuboidToBeMerged.cuboidX == current.cuboidX && cuboidToBeMerged.cuboidY == current.cuboidY)
                {
                    // if the two cuboids's width, height are the same
                    if (cuboidToBeMerged.width == current.width && cuboidToBeMerged.height == current.height)
                    {
                    }
                }

                //
            }
        }
    }
}

void sortCuboids(std::deque<Cuboid> &plane)
{
    std::sort(plane.begin(), plane.end(),
              [](const Cuboid &a, const Cuboid &b) -> bool
              {
                  if (a.blockY == b.blockY)
                  {
                      if (a.blockX == b.blockX)
                      {
                          if (a.cuboidY == b.cuboidY)
                          {
                              return a.cuboidX < b.cuboidX;
                          }
                          return a.cuboidY < b.cuboidY;
                      }
                      return a.blockX < b.blockX;
                  }
                  return a.blockY < b.blockY;
              });
}
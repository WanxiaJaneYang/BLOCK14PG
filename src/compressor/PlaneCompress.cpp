#include "Compressor.h"
#include <deque>
#include "../globals/globals.h"

std::deque<std::deque<Cuboid>> planeCompress(std::deque<std::deque<std::deque<Cuboid>>> &compressedLines)
{
    std::deque<std::deque<Cuboid>> result;
    // basic idea: read the matrix line by line,
    // if start point and end point of two lines are the same, plus the color is the same, then merge them into a rectangle
    // else if the either the start point or the end point is the same, plus the color is the same,
    // and the one below is longer than the one above, then split the one below into two rectangles, merge the one above with the first one
    // else push the cuboid

    // first read the plane by plane
    for (size_t z = 0; z < GlobalVars::depth; z++)
    {
        // read the plane line by line
        // current plane
        std::deque<std::deque<Cuboid>> plane = compressedLines[z];

        // this is var for compressed rectangles
        std::deque<Cuboid> compressedPlane;

        // this is var declared out of the loop
        std::deque<Cuboid> rectanglesToBeMerged;

        for (size_t y = 0; y < GlobalVars::height; y++)
        {
            // initialize the rectanglesToBeMerged if this is the first line
            if (y == 0)
            {
            }
            // if this is not the first line, compare the rectangles to see if they can be merged
            else
            {
                // hint: currently, the cuiboids are pushed in order
                // consider using while loop to merge the rectangles until the last one in the line is dealt
                std::deque<Cuboid> currentLine = plane[y];
                // scheme:
                while (rectanglesToBeMerged.size() > 0 && currentLine.size() > 0)
                {
                    Cuboid rectangleToBeMerged = rectanglesToBeMerged.front();
                    Cuboid current = currentLine.front();

                    // check the coordinates of the two cuboid
                    // consider if we are to merge or not

                    // choose to pop the rectanglesToBeMerged or the currentLine

                    // push the merged cuboid into the compressedPlane

                    // reassign the rectanglesToBeMerged
                }
                // check if the rectanglesToBeMerged is empty or currentLine is empty,
                // deal with the remaining cuboids
            }
        }
    }
    return result;
}
#include "Compressor.h"
#include <deque>
#include "../globals/globals.h"

std::deque<std::deque<Cuboid>> planeCompress(std::deque<std::deque<std::deque<Cuboid>>> &compressedLines)
{
    std::deque<std::deque<Cuboid>> result;
    // basic idea: read the matrix line by line,
    // if start point and end point of two lines are the same, plus the color is the same, then merge them into a rectangle
    // else if the either the start point or the end point is the same, plus the color is the same,
    // and the one below is longer than the one above, then split the one below into two rectangles, merge the one above with the overlap part
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
                rectanglesToBeMerged = plane[y];
            }
            // if this is not the first line, compare the rectangles to see if they can be merged
            else
            {
                // hint: currently, the cuboids are pushed in order
                // consider using while loop to merge the rectangles until the last one in the line is dealt
                std::deque<Cuboid> currentLine = plane[y];
                // scheme:
                while (rectanglesToBeMerged.size() > 0 && currentLine.size() > 0)
                {
                    Cuboid rectangleToBeMerged = rectanglesToBeMerged.front();
                    Cuboid current = currentLine.front();

                    // rectangleToBeMerged start point and end point
                    int rectangleStart = rectangleToBeMerged.cuboidX;
                    int rectangleEnd = rectangleStart + rectangleToBeMerged.width;

                    // current cuboid start point and end point
                    int currentStart = current.cuboidX;
                    int currentEnd = currentStart + current.width;

                    // check the coordinates of the two cuboids rectangleToBeMerged and current
                    // consider if we can merge them or not
                    if (rectangleStart == currentStart && rectangleToBeMerged.tag == current.tag)
                    {
                        // if the current cuboid's width is equal or greater than rectangleToBeMerged
                        if (current.width >= rectangleToBeMerged.width)
                        {
                            currentLine.pop_front();
                            rectanglesToBeMerged.pop_front();
                            // merge the two cuboids' overlap part
                            // push the merged cuboid into rectanglesToBeMerged queue
                            rectangleToBeMerged.height += current.height;
                            rectanglesToBeMerged.push_back(rectangleToBeMerged);

                            // check if the current cuboid has extra part after merge
                            int currentExtra = current.width - rectangleToBeMerged.width;
                            if (currentExtra > 0)
                            {
                                // change the coordinates of current cuboid extra part
                                current.cuboidX += rectangleToBeMerged.width;
                                current.width = currentExtra;

                                // the currentline front would be the cuboid's extra part after merge
                                currentLine.push_front(current);
                            }
                        }
                        else
                        {
                            // when current is shorter, we do not merge them
                            // pop and push the rectangleToBeMerged cuboid into the compressedPlane
                            rectanglesToBeMerged.pop_front();
                            compressedPlane.push_back(rectangleToBeMerged);

                            // pop and push the current cuboid into the rectanglesToBeMerged
                            currentLine.pop_front();
                            rectanglesToBeMerged.push_back(current);
                        }
                    }
                    // if the two cuboids have same end points and tags
                    else if (rectangleEnd == currentEnd && rectangleToBeMerged.tag == current.tag)
                    {
                        // if the current cuboid's width is greater than rectangleToBeMerged
                        if (current.width > rectangleToBeMerged.width)
                        {
                            currentLine.pop_front();
                            rectanglesToBeMerged.pop_front();
                            // merge the two cuboids' overlap part
                            // push the merged cuboid into rectanglesToBeMerged queue
                            rectangleToBeMerged.height += current.height;
                            rectanglesToBeMerged.push_back(rectangleToBeMerged);

                            // change the width of current cuboid as extra part's width
                            current.width = current.width - rectangleToBeMerged.width;

                            // push current cuboid's extra part into rectanglesToBeMerged
                            rectanglesToBeMerged.push_back(current);
                        }
                        else if (current.width < rectangleToBeMerged.width)
                        {
                            // when current is shorter
                            // pop and push the rectangleToBeMerged cuboid into the compressedPlane
                            rectanglesToBeMerged.pop_front();
                            compressedPlane.push_back(rectangleToBeMerged);

                            // pop and push the current cuboid into the rectanglesToBeMerged
                            currentLine.pop_front();
                            rectanglesToBeMerged.push_back(current);
                        }
                    }
                    else
                    {
                        // when these two cuboids have different start points, end points or tags
                        // if current cuboid endpoint is after the rectangleToBeMerged
                        // pop and push the rectangleToBeMerged cuboid into the compressedPlane
                        if (currentEnd >= rectangleEnd)
                        {
                            rectanglesToBeMerged.pop_front();
                            compressedPlane.push_back(rectangleToBeMerged);
                        }

                        // pop and push the current cuboid into the rectanglesToBeMerged
                        // if the rectangleToBeMerged endpoint is after current cuboid
                        if (currentEnd <= rectangleEnd)
                        {
                            currentLine.pop_front();
                            rectanglesToBeMerged.push_back(current);
                        }
                    }
                }
                // push all remaining current cuboid into the rectanglesToBeMerged
                while (currentLine.size() > 0)
                {
                    rectanglesToBeMerged.push_back(currentLine.front());
                    currentLine.pop_front();
                }
            }
        }
        // push all remaining rectangles into the compressedPlane
        while (rectanglesToBeMerged.size() > 0)
        {
            compressedPlane.push_back(rectanglesToBeMerged.front());
            rectanglesToBeMerged.pop_front();
        }
        result.push_back(compressedPlane);
    }
    return result;
}
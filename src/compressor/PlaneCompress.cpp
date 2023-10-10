#include "Compressor.h"
#include <deque>
#include "../globals/globals.h"

// check if there is matched cuboid in next line
bool matchNextLine(Cuboid cuboid, std::deque<Cuboid> nextLine)
{
    while (nextLine.size() > 0)
    {
        Cuboid current = nextLine.front();
        // exceed the comparison range, exit the loop
        if (current.cuboidX > cuboid.cuboidX)
        {
            break;
        }

        // if current cuboid in nextLine can overlap with cuboid in previous line
        if (current.cuboidX == cuboid.cuboidX && current.tag == cuboid.tag)
        {
            if (current.width == cuboid.width)
            {
                return true;
            }
        }
        nextLine.pop_front();
    }
    return false;
}

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
                while (rectanglesToBeMerged.front().cuboidY < y && currentLine.size() > 0)
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
                        bool canBeMerged = false;
                        // if the current cuboid's width is equal
                        if (current.width == rectangleToBeMerged.width)
                        {
                            currentLine.pop_front();
                            rectanglesToBeMerged.pop_front();
                            // merge the two cuboids' overlap part
                            // push the merged cuboid into rectanglesToBeMerged queue
                            rectangleToBeMerged.height += current.height;
                            rectanglesToBeMerged.push_back(rectangleToBeMerged);
                            canBeMerged = true;
                        }
                        else if (current.width > rectangleToBeMerged.width && y < GlobalVars::height - 1)
                        {
                            // if the currentline cuboid is longer, check if there is a matched cuboid in nextLine
                            std::deque<Cuboid> nextLine = plane[y + 1];
                            // intialise the two cuboids
                            Cuboid cuboid1 = current;
                            Cuboid cuboid2 = current;
                            // update the coordinates and width of cuboid1 and cuboid2
                            cuboid1.width = rectangleToBeMerged.width;
                            cuboid2.cuboidX = current.cuboidX + rectangleToBeMerged.width;
                            cuboid2.width = current.width - rectangleToBeMerged.width;
                            // if there is matched part in nextline
                            if (matchNextLine(cuboid1, nextLine) || matchNextLine(cuboid2, nextLine))
                            {
                                currentLine.pop_front();
                                rectanglesToBeMerged.pop_front();
                                // merge the two cuboids' overlap part
                                // push the merged cuboid into rectanglesToBeMerged queue
                                rectangleToBeMerged.height += cuboid1.height;
                                rectanglesToBeMerged.push_back(rectangleToBeMerged);
                                // the currentline front would be changed to the cuboid2
                                currentLine.push_front(cuboid2);
                                canBeMerged = true;
                            }
                        }

                        if (!canBeMerged)
                        {
                            // when current cuboid can not be split and merged
                            // while the rectangleToBeMerged endpoint is after current cuboid
                            while (currentEnd <= rectangleEnd && currentLine.size() > 0)
                            {
                                // pop and push the current cuboid into the rectanglesToBeMerged
                                rectanglesToBeMerged.push_back(currentLine.front());
                                currentLine.pop_front();
                                if (currentLine.size() > 0)
                                {
                                    currentEnd = currentLine.front().cuboidX + currentLine.front().width;
                                }
                            }

                            // pop and push the rectangleToBeMerged into compressedplane
                            rectanglesToBeMerged.pop_front();
                            compressedPlane.push_back(rectangleToBeMerged);
                        }
                    }
                    // if the two cuboids have same end points and tags
                    else if (rectangleEnd == currentEnd && rectangleToBeMerged.tag == current.tag)
                    {
                        bool canBeMerged = false;
                        // if the current cuboid's width is greater than rectangleToBeMerged
                        if (current.width > rectangleToBeMerged.width && y < GlobalVars::height - 1)
                        {

                            // if the currentline cuboid is longer, check if there is a matched cuboid in nextLine
                            std::deque<Cuboid> nextLine = plane[y + 1];
                            // intialise the two cuboids
                            Cuboid cuboid1 = current;
                            Cuboid cuboid2 = current;
                            // update the coordinates and width of cuboid1 and cuboid2
                            cuboid1.width = current.width - rectangleToBeMerged.width;
                            cuboid2.cuboidX = current.cuboidX + cuboid1.width;
                            cuboid2.width = rectangleToBeMerged.width;
                            // if there is matched part in nextline
                            if (matchNextLine(cuboid1, nextLine) || matchNextLine(cuboid2, nextLine))
                            {
                                currentLine.pop_front();
                                rectanglesToBeMerged.pop_front();

                                // push cuboid1 into rectanglesToBeMerged
                                rectanglesToBeMerged.push_back(cuboid1);

                                // merge cuboid2 and rectangle above
                                // push the merged cuboid into rectanglesToBeMerged queue
                                rectangleToBeMerged.height += cuboid2.height;
                                rectanglesToBeMerged.push_back(rectangleToBeMerged);
                                canBeMerged = true;
                            }
                        }

                        if (!canBeMerged)
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
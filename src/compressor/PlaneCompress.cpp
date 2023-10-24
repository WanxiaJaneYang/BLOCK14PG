// #include "Compressor.h"
// #include <deque>
// #include "../globals/globals.h"

// // check if there is a matched cuboid in next line
// bool matchNextLine(Cuboid cuboid, std::deque<Cuboid> nextLine)
// {
//     while (nextLine.size() > 0)
//     {
//         Cuboid next = nextLine.front();
//         // exceed the comparison range, exit the loop
//         if (next.cuboidX > cuboid.cuboidX)
//         {
//             break;
//         }

//         // if next cuboid in nextLine can overlap with cuboid in previous line
//         if (next.cuboidX == cuboid.cuboidX && next.tag == cuboid.tag)
//         {
//             if (next.width == cuboid.width)
//             {
//                 return true;
//             }
//         }
//         nextLine.pop_front();
//     }
//     return false;
// }

// // check if it is needed to continue searching cuboid in next line
// bool continueNextLine(Cuboid rect, std::deque<Cuboid> nextLine)
// {
//     while (nextLine.size() > 0)
//     {
//         Cuboid next = nextLine.front();
//         // exceed the comparison range, exit the loop
//         if (next.cuboidX > rect.cuboidX)
//         {
//             break;
//         }

//         int nextEnd = next.cuboidX + next.width;
//         int rectEnd = rect.cuboidX + rect.width;

//         // check if the same tag cuboid in next line can cover the width of first line rectangle
//         // same start
//         if (next.cuboidX == rect.cuboidX && next.tag == rect.tag)
//         {
//             if (next.width > rect.width)
//             {
//                 return true;
//             }
//         }
//         // or same ending
//         else if (nextEnd == rectEnd && next.tag == rect.tag)
//         {
//             if (next.width > rect.width)
//             {
//                 return true;
//             }
//         }
//         nextLine.pop_front();
//     }
//     return false;
// }

// // pop the cuboids and push into currect queues when they cannot be merged
// void handleNotMergedCuboids(std::deque<Cuboid> &rectanglesToBeMerged, std::deque<Cuboid> &currentLine, int currentEnd, int rectEnd)
// {
//     // while current cuboid's end is before rectangleToBeMerged's end
//     while (currentEnd <= rectEnd && currentLine.size() > 0)
//     {
//         // pop and push the current cuboid into the rectanglesToBeMerged
//         rectanglesToBeMerged.push_back(currentLine.front());
//         currentLine.pop_front();
//         if (currentLine.size() > 0)
//         {
//             currentEnd = currentLine.front().cuboidX + currentLine.front().width;
//         }
//     }

//     // pop rectangle
//     rectanglesToBeMerged.pop_front();
// }

// void planeCompress(std::deque<std::deque<std::deque<Cuboid>>> &compressedLines)
// {
//     std::deque<std::deque<Cuboid>> result;
//     // basic idea: read the matrix line by line,
//     // if start point and end point of two lines are the same, plus the color is the same, then merge them into a rectangle
//     // else if the either the start point or the end point is the same, plus the color is the same,
//     // and the one below is longer than the one above, then check the cuboid in next line to determine whether split and merge the current cuboid
//     // else push the cuboid

//     // first read the plane by plane
//     for (size_t z = 0; z < GlobalVars::depth; z++)
//     {
//         // read the plane line by line
//         // current plane
//         std::deque<std::deque<Cuboid>> plane = compressedLines[z];

//         // this is var for compressed rectangles
//         std::deque<Cuboid> compressedPlane;

//         // this is var declared out of the loop
//         std::deque<Cuboid> rectanglesToBeMerged;

//         for (size_t y = 0; y < GlobalVars::height; y++)
//         {
//             // initialize the rectanglesToBeMerged if this is the first line
//             if (y == 0)
//             {
//                 rectanglesToBeMerged = plane[y];
//             }
//             // if this is not the first line, compare the rectangles to see if they can be merged
//             else
//             {
//                 // hint: currently, the cuboids are pushed in order
//                 // consider using while loop to merge the rectangles until the last one in the line is dealt
//                 std::deque<Cuboid> currentLine = plane[y];
//                 // scheme:
//                 while (rectanglesToBeMerged.front().cuboidY < y && currentLine.size() > 0)
//                 {
//                     Cuboid rectangleToBeMerged = rectanglesToBeMerged.front();
//                     Cuboid current = currentLine.front();

//                     // rectangleToBeMerged start point and end point
//                     int rectangleStart = rectangleToBeMerged.cuboidX;
//                     int rectangleEnd = rectangleStart + rectangleToBeMerged.width;

//                     // current cuboid start point and end point
//                     int currentStart = current.cuboidX;
//                     int currentEnd = currentStart + current.width;
//                     bool canBeMerged = false;

//                     // check the coordinates of the two cuboids rectangleToBeMerged and current
//                     // consider if we can merge them or not
//                     if (rectangleStart == currentStart && rectangleToBeMerged.tag == current.tag)
//                     {
//                         // if the current cuboid's width is equal
//                         if (current.width == rectangleToBeMerged.width)
//                         {
//                             currentLine.pop_front();
//                             rectanglesToBeMerged.pop_front();
//                             // merge the two cuboids' overlap part
//                             // push the merged cuboid into rectanglesToBeMerged queue
//                             rectangleToBeMerged.height += current.height;
//                             rectanglesToBeMerged.push_back(rectangleToBeMerged);
//                             canBeMerged = true;
//                         }
//                         else if (current.width > rectangleToBeMerged.width && y < GlobalVars::height - 1)
//                         {
//                             // if the currentline cuboid is longer
//                             // intialise the two cuboids to represent two parts of current cuboid
//                             Cuboid cuboid1 = current;
//                             Cuboid cuboid2 = current;

//                             // update the coordinates and width of overlapped and extra cuboid
//                             cuboid1.width = rectangleToBeMerged.width;
//                             cuboid2.cuboidX = current.cuboidX + rectangleToBeMerged.width;
//                             cuboid2.width = current.width - rectangleToBeMerged.width;
//                             Cuboid extra = cuboid2;

//                             // nextLine is the currentLine's y + 1 in plane
//                             int next_y = y + 1;
//                             std::deque<Cuboid> nextLine = plane[next_y];

//                             // if cuboid in next line can cover rectangle above, continue read next line
//                             while (continueNextLine(rectangleToBeMerged, nextLine) && next_y < GlobalVars::height - 1)
//                             {
//                                 // update nextLine
//                                 next_y += 1;
//                                 nextLine = plane[next_y];
//                             }

//                             // copy a new rectangle deque for searching another rect at current's end
//                             std::deque<Cuboid> rectangles = rectanglesToBeMerged;
//                             rectangles.pop_front();
//                             Cuboid rect = rectangles.front();
//                             int rectEnd = rect.cuboidX + rect.width;

//                             // while rectangles are within the current cuboid length
//                             // searching if there is another same rectangle at current's end
//                             while (rectEnd <= currentEnd)
//                             {
//                                 if (rect.tag == current.tag && rectEnd == currentEnd && rect.cuboidX != rectangleEnd)
//                                 {
//                                     // update the extra and cuboid2
//                                     extra.width = rect.cuboidX - extra.cuboidX;
//                                     cuboid2.cuboidX = rect.cuboidX;
//                                     cuboid2.width = rect.width;
//                                 }

//                                 if (rectEnd < currentEnd)
//                                 {
//                                     rectangles.pop_front();
//                                     rect = rectangles.front();
//                                     rectEnd = rect.cuboidX + rect.width;
//                                 }
//                                 else
//                                 {
//                                     break;
//                                 }
//                             }

//                             // check if cuboids in nextline can match overlapped or extra cuboid
//                             if (matchNextLine(cuboid1, nextLine) || matchNextLine(extra, nextLine))
//                             {
//                                 rectanglesToBeMerged.pop_front();
//                                 //  merge the two cuboids' overlap part
//                                 //  push the merged cuboid into rectanglesToBeMerged queue
//                                 rectangleToBeMerged.height += cuboid1.height;
//                                 rectanglesToBeMerged.push_back(rectangleToBeMerged);
//                                 // update currentLine front
//                                 currentLine.front() = cuboid2;
//                                 if (extra.cuboidX != cuboid2.cuboidX)
//                                 {
//                                     currentLine.push_front(extra);
//                                 }
//                                 canBeMerged = true;
//                             }
//                         }
//                     }
//                     // if the two cuboids have same end points and tags
//                     else if (rectangleEnd == currentEnd && rectangleToBeMerged.tag == current.tag)
//                     {
//                         // if the current cuboid's width is greater than rectangleToBeMerged
//                         if (current.width > rectangleToBeMerged.width && y < GlobalVars::height - 1)
//                         {
//                             // intialise the two cuboids
//                             Cuboid cuboid1 = current;
//                             Cuboid cuboid2 = current;
//                             // update the coordinates and width of cuboid1 and cuboid2
//                             cuboid1.width = current.width - rectangleToBeMerged.width;
//                             cuboid2.cuboidX = current.cuboidX + cuboid1.width;
//                             cuboid2.width = rectangleToBeMerged.width;

//                             // nextLine is the currentLine's y + 1 in plane
//                             int next_y = y + 1;
//                             std::deque<Cuboid> nextLine = plane[next_y];

//                             // if cuboid in next line can cover rectangle above, continue read next line
//                             while (continueNextLine(rectangleToBeMerged, nextLine) && next_y < GlobalVars::height - 1)
//                             {
//                                 // update nextLine
//                                 next_y += 1;
//                                 nextLine = plane[next_y];
//                             }

//                             // if there is matched part in nextline
//                             if (matchNextLine(cuboid1, nextLine) || matchNextLine(cuboid2, nextLine))
//                             {
//                                 currentLine.pop_front();
//                                 rectanglesToBeMerged.pop_front();

//                                 // push cuboid1 into rectanglesToBeMerged
//                                 rectanglesToBeMerged.push_back(cuboid1);

//                                 // merge cuboid2 and the rectangle above
//                                 // push the merged cuboid into rectanglesToBeMerged queue
//                                 rectangleToBeMerged.height += cuboid2.height;
//                                 rectanglesToBeMerged.push_back(rectangleToBeMerged);
//                                 canBeMerged = true;
//                             }
//                         }
//                     }
//                     else if (rectangleStart > currentStart && rectangleToBeMerged.tag == current.tag)
//                     {
//                         // different start points and end points
//                         // rectangle cuboid is shorter and within the current cuboid range
//                         if (rectangleEnd < currentEnd && y < GlobalVars::height - 1)
//                         {
//                             // intialise the two cuboids
//                             Cuboid cuboid1 = current;
//                             Cuboid cuboid2 = current;
//                             // update the coordinates and width of cuboid1 and cuboid2
//                             // cuboid 1 is the extra part before rectangleToBeMerged
//                             cuboid1.width = rectangleStart - currentStart;
//                             // cuboid 2 is the extra part after rectangleToBeMerged
//                             cuboid2.cuboidX = rectangleEnd;
//                             cuboid2.width = currentEnd - rectangleEnd;

//                             // nextLine is the currentLine's y + 1 in plane
//                             int next_y = y + 1;
//                             std::deque<Cuboid> nextLine = plane[next_y];

//                             // when current cuboid can have overlapped cuboid in next line, continue reading next line
//                             while (matchNextLine(current, nextLine) && next_y < GlobalVars::height - 1)
//                             {
//                                 // update nextLine
//                                 next_y += 1;
//                                 nextLine = plane[next_y];
//                             }

//                             // if cuboid1 and cuboid2 can be matched in next line
//                             if (matchNextLine(cuboid1, nextLine) && matchNextLine(cuboid2, nextLine))
//                             {
//                                 rectanglesToBeMerged.pop_front();

//                                 // push cuboid1 into rectanglesToBeMerged
//                                 rectanglesToBeMerged.push_back(cuboid1);

//                                 // merge current's middle part to the rectangle above
//                                 // push the merged cuboid into rectanglesToBeMerged queue
//                                 rectangleToBeMerged.height += current.height;
//                                 rectanglesToBeMerged.push_back(rectangleToBeMerged);

//                                 // the currentline front would be the cuboid2
//                                 currentLine.front() = cuboid2;
//                                 canBeMerged = true;
//                             }
//                         }
//                     }

//                     // when these two cuboids have different tags
//                     // or they cannot be merged in the conditions above
//                     if (!canBeMerged)
//                     {
//                         handleNotMergedCuboids(rectanglesToBeMerged, currentLine, currentEnd, rectangleEnd);
//                         // compressedPlane.push_back(rectangleToBeMerged);
//                         GlobalVars::outputTasks.push(rectangleToBeMerged);
//                     }
//                 }
//             }
//         }
//         // push all remaining rectangles into the compressedPlane
//         while (rectanglesToBeMerged.size() > 0)
//         {
//             // compressedPlane.push_back(rectanglesToBeMerged.front());
//             GlobalVars::outputTasks.push(rectanglesToBeMerged.front());

//             rectanglesToBeMerged.pop_front();
//         }
//         // result.push_back(compressedPlane);
//     }
//     // return result;
// }
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
                    if (rectangleToBeMerged.tag == current.tag && rectangleStart == currentStart)
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
                            // while the rectangleToBeMerged endpoint is after current cuboid
                            while (currentEnd <= rectangleEnd)
                            {
                                // pop and push the current cuboid into the rectanglesToBeMerged
                                rectanglesToBeMerged.push_back(currentLine.front());
                                currentLine.pop_front();
                                if (currentLine.size() > 0)
                                {
                                    currentEnd = currentLine.front().cuboidX + currentLine.front().width;
                                }
                                else
                                {
                                    break;
                                }
                            }

                            // pop and push the rectangleToBeMerged into compressedplane
                            rectanglesToBeMerged.pop_front();
                            compressedPlane.push_back(rectangleToBeMerged);
                            // GlobalVars::outputTasks.push(rectangleToBeMerged);

                        }
                    }
                    // if the two cuboids have same end points and tags
                    else if (rectangleToBeMerged.tag == current.tag && rectangleEnd == currentEnd)
                    {
                        // if the current cuboid's width is greater than rectangleToBeMerged
                        if (current.width > rectangleToBeMerged.width)
                        {
                            currentLine.pop_front();
                            rectanglesToBeMerged.pop_front();
                            // change the width of current cuboid as extra part's width
                            current.width = current.width - rectangleToBeMerged.width;

                            // push current cuboid's extra part into rectanglesToBeMerged
                            rectanglesToBeMerged.push_back(current);

                            // merge the two cuboids' overlap part
                            // push the merged cuboid into rectanglesToBeMerged queue
                            rectangleToBeMerged.height += current.height;
                            rectanglesToBeMerged.push_back(rectangleToBeMerged);
                        }
                        else if (current.width < rectangleToBeMerged.width)
                        {
                            // when current is shorter
                            // pop and push the rectangleToBeMerged cuboid into the compressedPlane
                            rectanglesToBeMerged.pop_front();
                            compressedPlane.push_back(rectangleToBeMerged);
                            // GlobalVars::outputTasks.push(rectangleToBeMerged);

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
                            // GlobalVars::outputTasks.push(rectangleToBeMerged);

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
            // GlobalVars::outputTasks.push(rectanglesToBeMerged.front());

            rectanglesToBeMerged.pop_front();
        }
        result.push_back(compressedPlane);
    }
    // GlobalVars::outputTasks.push(result);
    return result;
}
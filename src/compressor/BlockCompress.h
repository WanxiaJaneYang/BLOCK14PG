#ifndef BLOCK_COMPRESS_H
#define BLOCK_COMPRESS_H

#include <deque>
#include <map>
#include "../globals/globals.h"
#include "../cores/SafeOutputTasks.h"
#include <algorithm>
void blockCompress(std::deque<std::deque<Cuboid>> &planes);
struct Point
{
    int x;
    int y;
    Point(int x = 0, int y = 0); // Added default values to keep the same struct constructor.
    bool operator==(const Point &other) const;
};

struct CuboidKey
{
    char tag;
    Point topLeft;
    Point bottomRight;
    bool operator<(const CuboidKey &other) const;
    bool operator==(const CuboidKey &other) const;
};

struct RemainingCuboid
{
    Cuboid upper;
    Cuboid left;
    Cuboid right;
    Cuboid lower;
};

#ifdef TESTING

RemainingCuboid minusCuboid(const Cuboid &currentCuboid, const Cuboid &prevCuboid);
bool findAllMatched(RemainingCuboid &remainingCuboid, std::map<CuboidKey, Cuboid> &nextPlane);
void transformToMap(std::deque<Cuboid> &plane, std::map<CuboidKey, Cuboid> &cuboids);
void pushRemainIntoMerge(RemainingCuboid &remain, std::map<CuboidKey, Cuboid> &mergedPlane);
bool isOverLapped(const CuboidKey &cuboid1, const CuboidKey &cuboid2);
#endif
#endif

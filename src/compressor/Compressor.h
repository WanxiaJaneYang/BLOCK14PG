#include <deque>
#include "../cores/Block.h"
#include "../cores/Cuboid.h"
#include <map>
#ifndef COMPRESSOR_H
#define COMPRESSOR_H

void compress();
std::deque<std::deque<std::deque<Cuboid>>> lineCompress(Block &block);
std::deque<std::deque<Cuboid>> planeCompress(std::deque<std::deque<std::deque<Cuboid>>> &compressedLines);
void blockCompress(std::deque<std::deque<Cuboid>> &planes);

#ifdef TESTING
// helper functions from blockCompress
struct Point
{
    int x;
    int y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    // overload the == operator for comparing
    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }
};

struct CuboidKey
{
    Point topLeft;
    Point bottomRight;

    // overload the < operator, so that the map can be sorted
    bool operator<(const CuboidKey &other) const
    {
        if (topLeft.y != other.topLeft.y)
            return topLeft.y < other.topLeft.y;
        return topLeft.x < other.topLeft.x;
    }

    // overload the == operator for comparing
    bool operator==(const CuboidKey &other) const
    {
        return topLeft.x == other.topLeft.x && topLeft.y == other.topLeft.y && bottomRight.x == other.bottomRight.x && bottomRight.y == other.bottomRight.y;
    }
};

struct RemainingCuboid
{
    Cuboid upper;
    Cuboid left;
    Cuboid right;
    Cuboid lower;
};

RemainingCuboid minus(const Cuboid &currentCuboid, const Cuboid &prevCuboid);
bool findAllMatched(RemainingCuboid &remainingCuboid, std::map<CuboidKey, Cuboid> &nextPlane);
void pushRemainIntoMerge(RemainingCuboid &remain, std::map<CuboidKey, Cuboid> &mergedPlane);
void tranformToMap(std::deque<Cuboid> &plane, std::map<CuboidKey, Cuboid> &cuboids);
#endif

#endif
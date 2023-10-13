#ifndef BLOCK_COMPRESS_H
#define BLOCK_COMPRESS_H

#include <deque>
#include <map>
#include "../globals/globals.h"
#include "../cores/SafeOutputTasks.h"
#include <algorithm>
#include <set>
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

#ifdef TESTING

void transformToMap(std::deque<Cuboid> &plane, std::map<CuboidKey, Cuboid> &cuboids);
bool isOverLapped(const CuboidKey &cuboid1, const CuboidKey &cuboid2);
bool isAContainsB(const CuboidKey &a, const CuboidKey &b);
void CuboidsInSameArea(std::map<CuboidKey, Cuboid> &prevPlane, std::map<CuboidKey, Cuboid> &cuboidsFromPrevPlane, std::map<CuboidKey, Cuboid> &nextPlane, std::map<CuboidKey, Cuboid> &cuboidsFromNextPlane, CuboidKey &middleCuboid);
void retrieveUniqueAndNonOverlapping(std::map<CuboidKey, Cuboid> &cuboidsFromPrevPlane,std::map<CuboidKey, Cuboid> &cuboidsFromNextPlane,std::set<CuboidKey> &uniqueCuboids,std::set<CuboidKey> &nonOverlappedCuboids);
int tryMerge(std::map<CuboidKey, Cuboid> &cuboidsFromPrevPlane,std::map<CuboidKey, Cuboid> &cuboidsFromNextPlane, CuboidKey &middleCuboid, std::set<CuboidKey> &dividedCuboids);
void divide(std::set<CuboidKey> nonOverlappedCuboids,CuboidKey &middleCuboid, std::set<CuboidKey> &dividedCuboids);
#endif
#endif

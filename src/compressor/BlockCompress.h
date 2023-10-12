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

#ifdef TESTING

void transformToMap(std::deque<Cuboid> &plane, std::map<CuboidKey, Cuboid> &cuboids);
bool isOverLapped(const CuboidKey &cuboid1, const CuboidKey &cuboid2);
bool isAContainsB(const CuboidKey &a, const CuboidKey &b);
/*
 * @param prevPlane: the previous plane
 * @param nextPlane: the next plane
 * @param cuboidsFromPrevPlane: the cuboids from the previous plane in the same area
 * @param cuboidsFromNextPlane: the cuboids from the next plane in the same area
 */

#endif
#endif

#define TESTING

#include <map>
#include "../../../../../src/compressor/Compressor.h"
#include "unitTestHelpers.h"

bool areCuboidsEqual(const Cuboid &expected, const Cuboid &actual)
{
    if (expected.blockX != actual.blockX)
    {
        return false;
    }

    if (expected.blockY != actual.blockY)
    {
        return false;
    }

    if (expected.blockZ != actual.blockZ)
    {
        return false;
    }

    if (expected.cuboidX != actual.cuboidX)
    {
        return false;
    }

    if (expected.cuboidY != actual.cuboidY)
    {
        return false;
    }

    if (expected.cuboidZ != actual.cuboidZ)
    {
        return false;
    }

    if (expected.width != actual.width)
    {
        return false;
    }

    if (expected.height != actual.height)
    {
        return false;
    }

    if (expected.depth != actual.depth)
    {
        return false;
    }

    if (expected.tag != actual.tag)
    {
        return false;
    }

    return true;
}

bool areMapsEqual(const std::map<CuboidKey, Cuboid> &expected, const std::map<CuboidKey, Cuboid> &actual)
{
    if (expected.size() != actual.size())
    {
        return false;
    }

    for (const auto &pair : expected)
    {
        const CuboidKey &key = pair.first;
        const Cuboid &value = pair.second;

        if (actual.find(key) == actual.end())
        {
            return false;
        }

        if (!areCuboidsEqual(value, actual.at(key)))
        {
            return false;
        }
    }

    return true;
}
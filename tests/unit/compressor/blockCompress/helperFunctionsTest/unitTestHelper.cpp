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

std::string cuboidToString(const Cuboid &cuboid)
{
    std::string cuboidString = "(" + std::to_string(cuboid.blockX) + "," + std::to_string(cuboid.blockY) + "," + std::to_string(cuboid.blockZ) + "),";
    cuboidString += "(" + std::to_string(cuboid.cuboidX) + "," + std::to_string(cuboid.cuboidY) + "," + std::to_string(cuboid.cuboidZ) + "),";
    cuboidString += "(" + std::to_string(cuboid.width) + "," + std::to_string(cuboid.height) + "," + std::to_string(cuboid.depth) + "),";
    cuboidString += cuboid.tag;

    return cuboidString;
}

std::string cuboidKeyToString(const CuboidKey &cuboidKey)
{
    std::string cuboidKeyString = "";

    cuboidKeyString += "tag: " + std::to_string(cuboidKey.tag) + ",";
    cuboidKeyString += "topLeft: (" + std::to_string(cuboidKey.topLeft.x) + "," + std::to_string(cuboidKey.topLeft.y) + "),";
    cuboidKeyString += "bottomRight: (" + std::to_string(cuboidKey.bottomRight.x) + "," + std::to_string(cuboidKey.bottomRight.y) + ")";
    return cuboidKeyString;
}

bool compareCuboid(const Cuboid &cuboid1, const Cuboid &cuboid2)
{
    // sorting priorities: first z, then y, then x
    if (cuboid1.cuboidZ < cuboid2.cuboidZ)
    {
        return true;
    }
    else if (cuboid1.cuboidZ > cuboid2.cuboidZ)
    {
        return false;
    }
    else
    {
        if (cuboid1.cuboidY < cuboid2.cuboidY)
        {
            return true;
        }
        else if (cuboid1.cuboidY > cuboid2.cuboidY)
        {
            return false;
        }
        else
        {
            if (cuboid1.cuboidX < cuboid2.cuboidX)
            {
                return true;
            }
            else if (cuboid1.cuboidX > cuboid2.cuboidX)
            {
                return false;
            }
            else
            {
                return false;
            }
        }
    }
}

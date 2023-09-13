#include "BlockCompress.h"

/*compress the planes into cuboid and push them into output tasks*/
void blockCompress(std::deque<std::deque<Cuboid>> &planes)
{
    // declare a map to store the previous plane, basically plane might be able to be further merged
    // or might not be. the key is the x and y of the top left corner of the cuboid
    std::map<CuboidKey, Cuboid> prevPlane;
    // read plane by plane
    for (size_t z = 0; z < GlobalVars::depth; z++)
    {
        if (z == 0)
        {
            // this is the first plane
            transformToMap(planes[z], prevPlane);
        }
        else
        {
            // from the second plane
            std::map<CuboidKey, Cuboid> currentPlane;
            transformToMap(planes[z], currentPlane);

            // this is the merged plane which will be later reassigned to prevPlane
            std::map<CuboidKey, Cuboid> mergedPlane;

            for (auto it = prevPlane.begin(); it != prevPlane.end();)
            {
                // if there is a cuboid has the same four points of the cuboid from prevPlane, merge it
                auto key = it->first;
                if (currentPlane.find(key) != currentPlane.end())
                {
                    // merge the cuboid
                    Cuboid cuboid = it->second;
                    cuboid.depth++;
                    // remove the cuboid from the current plane
                    currentPlane.erase(key);
                    // push the merged cuboid into the merged plane
                    mergedPlane[key] = cuboid;
                    // remove the cuboid from the prev plane
                    it = prevPlane.erase(it);
                }

                // we cannot find an exactly matched cuboid in the next plane
                else
                {
                    // find the case where the cuboid in the current plane
                    // contains the cuboid in the prev plane

                    // since all cuboids are sorted, if the current cuboid's top left corner is to the right/down of the prev cuboid's top left corner,
                    // or the bottom right corner is to the left/up of the prev cuboid's bottom right corner,
                    // then the current cuboid cannot contain the prev cuboid
                    if (key.topLeft.x > currentPlane.begin()->first.topLeft.x || key.topLeft.y < currentPlane.begin()->first.topLeft.y || key.bottomRight.x < currentPlane.rbegin()->first.bottomRight.x || key.bottomRight.y > currentPlane.rbegin()->first.bottomRight.y)
                    {
                        // push the cuboid into the output tasks
                        GlobalVars::outputTasks.push(it->second);
                        // remove the cuboid from the prev plane
                        it = prevPlane.erase(it);

                        // move the current cuboid to the merged plane
                        mergedPlane[currentPlane.begin()->first] = currentPlane.begin()->second;
                        // remove the cuboid from the current plane
                        currentPlane.erase(currentPlane.begin());
                    }
                    // case that the current cuboid contains the prev cuboid, but there is no next plane
                    else if (z == GlobalVars::depth - 1)
                    {
                        // push the cuboid from the prev plane into the output tasks
                        GlobalVars::outputTasks.push(it->second);
                        // remove the cuboid from the prev plane
                        it = prevPlane.erase(it);

                        // push the cuboid from the current plane into the output tasks
                        GlobalVars::outputTasks.push(currentPlane.begin()->second);
                    }
                    // case that the current cuboid contains the prev cuboid and there is nextplane
                    else
                    {
                        // calculate the remain part of the cuboid in the current plane minusCuboid the cuboid in the prev plane
                        RemainingCuboid remain = minusCuboid(currentPlane.begin()->second, it->second);
                        std::map<CuboidKey, Cuboid> nextPlane;
                        transformToMap(planes[z + 1], nextPlane);
                        // then we find if there are exact cuboids in the next plane matching the remain part
                        // examine the remainCuboid, see if there are cuboids in the next plane matching the remain part
                        if (findAllMatched(remain, nextPlane))
                        {
                            // if all matched, merge the cuboid in the prev plane with the cuboid in the current plane
                            // and push the merged cuboid into the merged plane
                            Cuboid merged = it->second;
                            merged.depth++;
                            mergedPlane[key] = merged;
                            // remove the cuboid from the prev plane
                            it = prevPlane.erase(it);

                            // get the cuboid in the remain and push it into the merged plane
                            pushRemainIntoMerge(remain, mergedPlane);

                            // remove the cuboid from the current plane
                            currentPlane.erase(currentPlane.begin());
                        }
                        else
                        {
                            // if not all matched, push the cuboid in the prev plane into the output tasks
                            GlobalVars::outputTasks.push(it->second);
                            // remove the cuboid from the prev plane
                            it = prevPlane.erase(it);

                            // and push the cuboid in the current plane into the merged plane
                            mergedPlane[currentPlane.begin()->first] = currentPlane.begin()->second;
                            // remove the cuboid from the current plane
                            currentPlane.erase(currentPlane.begin());
                        }
                    }
                }
                // mergedPlane is the current plane
            }

            // if there are cuboids left in the current plane, push them into the merged plane
            for (auto it = currentPlane.begin(); it != currentPlane.end();)
            {
                mergedPlane[it->first] = it->second;
                it = currentPlane.erase(it);
            }

            // reassign the merged plane to the prev plane
            prevPlane = mergedPlane;
        }
    }
}

RemainingCuboid minusCuboid(const Cuboid &currentCuboid, const Cuboid &prevCuboid)
{
    RemainingCuboid result;
    // Define uninitialized Cuboids with an invalid tag
    result.upper.tag = -1;
    result.left.tag = -1;
    result.right.tag = -1;
    result.lower.tag = -1;

    // duplicate the prevCuboid as the remain part
    Cuboid remain = Cuboid(currentCuboid.blockX, currentCuboid.blockY, currentCuboid.blockZ, currentCuboid.cuboidX, currentCuboid.cuboidY, currentCuboid.cuboidZ, currentCuboid.width, currentCuboid.height, currentCuboid.depth, currentCuboid.tag);
    // calculate the upper part
    if (currentCuboid.cuboidY < prevCuboid.cuboidY)
    {
        // update the result
        result.upper = Cuboid(currentCuboid.blockX, currentCuboid.blockY, currentCuboid.blockZ, currentCuboid.cuboidX, currentCuboid.cuboidY, currentCuboid.cuboidZ, currentCuboid.width, prevCuboid.cuboidY - currentCuboid.cuboidY, currentCuboid.depth, currentCuboid.tag);

        // update the remain part
        remain.cuboidY = prevCuboid.cuboidY;
        remain.height = currentCuboid.cuboidY + currentCuboid.height - prevCuboid.cuboidY;
    }

    // calculate the left part
    if (remain.cuboidX < prevCuboid.cuboidX)
    {
        // update the result
        result.left = Cuboid(remain.blockX, remain.blockY, remain.blockZ, remain.cuboidX, remain.cuboidY, remain.cuboidZ, prevCuboid.cuboidX - remain.cuboidX, remain.height, remain.depth, remain.tag);

        // update the remain part
        remain.cuboidX = prevCuboid.cuboidX;
        remain.width = remain.cuboidX + remain.width - prevCuboid.cuboidX;
    }

    // calculate the right part
    if (remain.cuboidX + remain.width > prevCuboid.cuboidX + prevCuboid.width)
    {
        // update the result
        result.right = Cuboid(remain.blockX, remain.blockY, remain.blockZ, prevCuboid.cuboidX + prevCuboid.width, remain.cuboidY, remain.cuboidZ, remain.cuboidX + remain.width - prevCuboid.cuboidX - prevCuboid.width, remain.height, remain.depth, remain.tag);

        // update the remain part
        remain.width = prevCuboid.cuboidX + prevCuboid.width - remain.cuboidX;
    }

    // calculate the lower part
    if (remain.cuboidY + remain.height > prevCuboid.cuboidY + prevCuboid.height)
    {
        // update the result
        result.lower = Cuboid(remain.blockX, remain.blockY, remain.blockZ, remain.cuboidX, prevCuboid.cuboidY + prevCuboid.height, remain.cuboidZ, remain.width, remain.cuboidY + remain.height - prevCuboid.cuboidY - prevCuboid.height, remain.depth, remain.tag);

        // update the remain part
        remain.height = prevCuboid.cuboidY + prevCuboid.height - remain.cuboidY;
    }

    // if there is left part and lower part, split the lower part into two parts and merge the left of the lower part with the left part
    if (result.left.tag != -1 && result.lower.tag != -1)
    {
        // update the left part to add the left part of the lower part
        result.left.height += result.lower.height;

        // update the lower part to remove the left part in the lower part
        result.lower.cuboidX += result.left.width;
        result.lower.width -= result.left.width;
    }

    // if there is right part and lower part, split the lower part into two parts and merge the right of the lower part with the right part
    if (result.right.tag != -1 && result.lower.tag != -1)
    {
        // update the right part to add the right part of the lower part
        result.right.height += result.lower.height;

        // update the lower part to remove the right part in the lower part
        result.lower.width -= result.right.width;
    }

    return result;
}

bool findAllMatched(RemainingCuboid &remainingCuboid, std::map<CuboidKey, Cuboid> &nextPlane)
{
    // check if the upper part is matched
    if (remainingCuboid.upper.tag != -1)
    {
        // check if there is a cuboid in the next plane matching the upper part
        auto it = nextPlane.find(CuboidKey{Point(remainingCuboid.upper.cuboidX, remainingCuboid.upper.cuboidY), Point(remainingCuboid.upper.cuboidX + remainingCuboid.upper.width - 1, remainingCuboid.upper.cuboidY + remainingCuboid.upper.height - 1)});
        if (it == nextPlane.end())
        {
            // if there is no cuboid matching the upper part, return false
            return false;
        }
    }

    // check if the left part is matched
    if (remainingCuboid.left.tag != -1)
    {
        // check if there is a cuboid in the next plane matching the left part
        auto it = nextPlane.find(CuboidKey{Point(remainingCuboid.left.cuboidX, remainingCuboid.left.cuboidY), Point(remainingCuboid.left.cuboidX + remainingCuboid.left.width - 1, remainingCuboid.left.cuboidY + remainingCuboid.left.height - 1)});
        if (it == nextPlane.end())
        {
            // if there is no cuboid matching the left part, return false
            return false;
        }
    }

    // check if the right part is matched
    if (remainingCuboid.right.tag != -1)
    {
        // check if there is a cuboid in the next plane matching the right part
        auto it = nextPlane.find(CuboidKey{Point(remainingCuboid.right.cuboidX, remainingCuboid.right.cuboidY), Point(remainingCuboid.right.cuboidX + remainingCuboid.right.width - 1, remainingCuboid.right.cuboidY + remainingCuboid.right.height - 1)});
        if (it == nextPlane.end())
        {
            // if there is no cuboid matching the right part, return false
            return false;
        }
    }

    // check if the lower part is matched
    if (remainingCuboid.lower.tag != -1)
    {
        // check if there is a cuboid in the next plane matching the lower part
        auto it = nextPlane.find(CuboidKey{Point(remainingCuboid.lower.cuboidX, remainingCuboid.lower.cuboidY), Point(remainingCuboid.lower.cuboidX + remainingCuboid.lower.width - 1, remainingCuboid.lower.cuboidY + remainingCuboid.lower.height - 1)});
        if (it == nextPlane.end())
        {
            // if there is no cuboid matching the lower part, return false
            return false;
        }
    }
    return true;
}

void pushRemainIntoMerge(RemainingCuboid &remain, std::map<CuboidKey, Cuboid> &mergedPlane)
{
    // push the remain part into the merged plane
    if (remain.upper.tag != -1)
    {
        mergedPlane[CuboidKey{Point(remain.upper.cuboidX, remain.upper.cuboidY), Point(remain.upper.cuboidX + remain.upper.width - 1, remain.upper.cuboidY + remain.upper.height - 1)}] = remain.upper;
    }
    if (remain.left.tag != -1)
    {
        mergedPlane[CuboidKey{Point(remain.left.cuboidX, remain.left.cuboidY), Point(remain.left.cuboidX + remain.left.width - 1, remain.left.cuboidY + remain.left.height - 1)}] = remain.left;
    }
    if (remain.right.tag != -1)
    {
        mergedPlane[CuboidKey{Point(remain.right.cuboidX, remain.right.cuboidY), Point(remain.right.cuboidX + remain.right.width - 1, remain.right.cuboidY + remain.right.height - 1)}] = remain.right;
    }
    if (remain.lower.tag != -1)
    {
        mergedPlane[CuboidKey{Point(remain.lower.cuboidX, remain.lower.cuboidY), Point(remain.lower.cuboidX + remain.lower.width - 1, remain.lower.cuboidY + remain.lower.height - 1)}] = remain.lower;
    }
}

void transformToMap(std::deque<Cuboid> &plane, std::map<CuboidKey, Cuboid> &cuboids)
{
    for (size_t i = 0; i < plane.size(); i++)
    {
        CuboidKey key = {
            Point(plane[i].cuboidX, plane[i].cuboidY),
            Point(plane[i].cuboidX + plane[i].width - 1, plane[i].cuboidY + plane[i].height - 1)};
        cuboids[key] = plane[i];
    }
}

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

bool Point::operator==(const Point &other) const
{
    return x == other.x && y == other.y;
}

bool CuboidKey::operator<(const CuboidKey &other) const
{
    if (topLeft.y != other.topLeft.y)
        return topLeft.y < other.topLeft.y;
    return topLeft.x < other.topLeft.x;
}

bool CuboidKey::operator==(const CuboidKey &other) const
{
    return topLeft == other.topLeft && bottomRight == other.bottomRight;
}

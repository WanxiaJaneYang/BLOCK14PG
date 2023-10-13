#include "BlockCompress.h"
#include <stdexcept>
#include <iostream>
#include <set>
/*
function to check if the two cuboids from different planes are overlapped
*/
bool isOverLapped(const CuboidKey &cuboid1, const CuboidKey &cuboid2)
{
    // if the two cuboids are overlapped, return true
    // if the bottom right corner of cuboid1 is to the left of the top left corner of cuboid2, return false
    if (cuboid1.bottomRight.x < cuboid2.topLeft.x)
    {
        return false;
    }
    // if the top left corner of cuboid1 is to the right of the bottom right corner of cuboid2, return false
    if (cuboid1.topLeft.x > cuboid2.bottomRight.x)
    {
        return false;
    }
    // if the bottom right corner of cuboid1 is above the top left corner of cuboid2, return false
    if (cuboid1.bottomRight.y < cuboid2.topLeft.y)
    {
        return false;
    }
    // if the top left corner of cuboid1 is below the bottom right corner of cuboid2, return false
    if (cuboid1.topLeft.y > cuboid2.bottomRight.y)
    {
        return false;
    }

    return true;
}

/*transform the plane into a map*/
void transformToMap(std::deque<Cuboid> &plane, std::map<CuboidKey, Cuboid> &cuboids)
{
    for (size_t i = 0; i < plane.size(); i++)
    {
        CuboidKey key = {
            plane[i].tag,
            Point(plane[i].cuboidX, plane[i].cuboidY),
            Point(plane[i].cuboidX + plane[i].width - 1, plane[i].cuboidY + plane[i].height - 1)};
        cuboids[key] = plane[i];
    }
}

// Added default values to keep the same struct constructor.
Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

// reload the operator == for the Point
bool Point::operator==(const Point &other) const
{
    return x == other.x && y == other.y;
}

// reload the operator < for the CuboidKey
bool CuboidKey::operator<(const CuboidKey &other) const
{
    if (topLeft.y != other.topLeft.y)
        return topLeft.y < other.topLeft.y;

    if (topLeft.x != other.topLeft.x)
        return topLeft.x < other.topLeft.x;

    if (bottomRight.y != other.bottomRight.y)
        return bottomRight.y < other.bottomRight.y;

    if (bottomRight.x != other.bottomRight.x)
        return bottomRight.x < other.bottomRight.x;

    return tag < other.tag;
}

// reload the operator == for the CuboidKey
bool CuboidKey::operator==(const CuboidKey &other) const
{
    return tag == other.tag && topLeft == other.topLeft && bottomRight == other.bottomRight;
}

/*
function to push the cuboids in the prev plane into the output tasks
*/
void pushPlaneIntoOutputTasks(std::map<CuboidKey, Cuboid> &prevPlane)
{
    for (auto it = prevPlane.begin(); it != prevPlane.end();)
    {
        GlobalVars::outputTasks.push(it->second);
        it = prevPlane.erase(it);
    }
}

bool isAContainsB(const CuboidKey &a, const CuboidKey &b)
{
    if (a.tag != b.tag)
    {
        return false;
    }

    if (a.topLeft.x > b.topLeft.x)
    {
        return false;
    }

    if (a.topLeft.y > b.topLeft.y)
    {
        return false;
    }

    if (a.bottomRight.x < b.bottomRight.x)
    {
        return false;
    }

    if (a.bottomRight.y < b.bottomRight.y)
    {
        return false;
    }

    return true;
}

void CuboidsInSameArea(std::map<CuboidKey, Cuboid> &prevPlane, std::map<CuboidKey, Cuboid> &cuboidsFromPrevPlane, std::map<CuboidKey, Cuboid> &nextPlane, std::map<CuboidKey, Cuboid> &cuboidsFromNextPlane, CuboidKey &middleCuboid)
{
    // iterate through the prev plane
    for (auto it = prevPlane.begin(); it!=prevPlane.end();it++)
    {
        // if the cuboid is in the same area as the middle cuboid
        if (isAContainsB(middleCuboid, it->first))
        {
            // push the cuboid into the cuboidsFromPrevPlane
            cuboidsFromPrevPlane[it->first] = it->second;
        }
    }
    

    // iterate through the next plane
    for (auto it = nextPlane.begin(); it!=nextPlane.end();it++)
    {
        // if the cuboid is in the same area as the middle cuboid
        if (isAContainsB(middleCuboid, it->first))
        {
            // push the cuboid into the cuboidsFromNextPlane
            cuboidsFromNextPlane[it->first] = it->second;
        }
    }
}

int tryMerge(std::map<CuboidKey, Cuboid> &cuboidsFromPrevPlane,std::map<CuboidKey, Cuboid> &cuboidsFromNextPlane, CuboidKey &middleCuboid, std::set<CuboidKey> &dividedCuboids){
    int count=0;
    std::set<CuboidKey> mergedCuboids;
    std::set<CuboidKey> nonOverlappedCuboids;
    for (auto it = cuboidsFromPrevPlane.begin(); it != cuboidsFromPrevPlane.end();it++)
    {
        mergedCuboids.insert(it->first);
    }

    for (auto it = cuboidsFromNextPlane.begin(); it != cuboidsFromNextPlane.end();it++)
    {
        mergedCuboids.insert(it->first);
        bool isOverlapped=false;
        for (auto it2 = cuboidsFromPrevPlane.begin(); it2 != cuboidsFromPrevPlane.end();it2++)
        {
            if(isOverLapped(it->first,it2->first)){
                isOverlapped=true;
                break;
            }
        }
        if(!isOverlapped){
            nonOverlappedCuboids.insert(it->first);
        }
    }

    count=mergedCuboids.size();

    //segement the middle cuboid by the merged cuboids
    std::vector<int> xVec;
    std::vector<int> yVec;

    xVec.push_back(middleCuboid.topLeft.x);
    xVec.push_back(middleCuboid.bottomRight.x);
    yVec.push_back(middleCuboid.topLeft.y);
    yVec.push_back(middleCuboid.bottomRight.y);
    for(auto it=nonOverlappedCuboids.begin();it!=nonOverlappedCuboids.end();it++){
        xVec.push_back(it->topLeft.x);
        xVec.push_back(it->bottomRight.x);
        yVec.push_back(it->topLeft.y);
        yVec.push_back(it->bottomRight.y);
    }

    //sort the x and y
    std::sort(xVec.begin(),xVec.end());
    std::sort(yVec.begin(),yVec.end());

    //form all the cuboids
    std::set<CuboidKey> allPossibleCuboids;
    for(int i=0;i<xVec.size()-1;i++){
        for(int j=0;j<yVec.size()-1;j++){
            CuboidKey cuboidKey={
                middleCuboid.tag,
                Point(xVec[i],yVec[j]),
                Point(xVec[i+1],yVec[j+1])
            };
            //check if the cuboid is overlapped with the merged cuboids or already exists
            if (mergedCuboids.find(cuboidKey) != mergedCuboids.end())
            {
                bool isOverlapped=false;
                for(auto it=mergedCuboids.begin();it!=mergedCuboids.end();it++){
                    if(isOverLapped(cuboidKey,*it)){
                        isOverlapped=true;
                        break;
                    }
                }
                if(!isOverlapped){
                    count+=1;
                    dividedCuboids.insert(cuboidKey);
                }
            }else{
                dividedCuboids.insert(cuboidKey);
            }
        }
    }

    //problem here: may have over segmentation cuboids
    return count;
}

/*compress the planes into cuboid and push them into output tasks*/
void blockCompress(std::deque<std::deque<Cuboid>> &planes)
{
    std::cout<<"planes size: "<<planes.size()<<std::endl;
    // declare a map to store the previous plane, basically plane might be able to be further merged
    // or might not be. the key is the x and y of the top left corner of the cuboid
    std::map<CuboidKey, Cuboid> prevPlane;
    transformToMap(planes[0], prevPlane);

    // read plane by plane
    for (size_t z = 1; z < planes.size(); z++)
    {
        std::cout << "z: " << z << std::endl;

        // from the second plane
        std::map<CuboidKey, Cuboid> currentPlane;
        transformToMap(planes[z], currentPlane);

        // this is the merged plane which will be later reassigned to prevPlane
        std::map<CuboidKey, Cuboid> mergedPlane;

        // iterate through the prev plane
        for (auto it = prevPlane.begin(); it != prevPlane.end();)
        {
            std::cout << "it: cuboidKey: " << it->first.tag << ", topLeft( " << it->first.topLeft.x << ", " << it->first.topLeft.y << "),( " << it->first.bottomRight.x << " " << it->first.bottomRight.y << ")" << std::endl;
            // if the current plane is empty, push the cuboid into the output tasks
            if (currentPlane.empty())
            {
                std::cout << "current plane is empty" << std::endl;
                pushPlaneIntoOutputTasks(prevPlane);
                break;
            }

            // if there is a cuboid has the same key in the current plane, merge the cuboid
            auto key = it->first;
            if (currentPlane.find(key) != currentPlane.end())
            {
                std::cout << "current plane has the same key" << std::endl;
                std::cout << "merge the cuboid" << std::endl;
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
            // if there is no cuboid has the same key in the current plane, and this is the last plane
            else if (z == planes.size() - 1)
            {
                std::cout << "last plane" << std::endl;
                std::cout << "push the cuboid into the output tasks" << std::endl;
                GlobalVars::outputTasks.push(it->second);
                // remove the cuboid from the prev plane
                it = prevPlane.erase(it);
            }

            // there is more planes to go and there is no cuboid has the same key in the current plane
            else
            {
                // if the two front cuboids do not overlap
                // push the cuboid in the prev plane into the output tasks
                if (!isOverLapped(key, currentPlane.begin()->first))
                {
                    // std::cout << "the two front cuboids do not overlap" << std::endl;
                    //  remove the cuboid with the smaller index
                    if (key < currentPlane.begin()->first)
                    {
                        // std::cout << "remove the cuboid from the prev plane" << std::endl;
                        GlobalVars::outputTasks.push(it->second);
                        // remove the cuboid from the prev plane
                        it = prevPlane.erase(it);
                    }
                    else
                    {
                        // std::cout << "remove the cuboid from the current plane to merged plane" << std::endl;
                        // push the cuboid in the current plane into the merged plane
                        mergedPlane[currentPlane.begin()->first] = currentPlane.begin()->second;
                        // remove the cuboid from the current plane
                        currentPlane.erase(currentPlane.begin());
                    }
                }

                // if the two front cuboids overlap
                // find the case where the cuboid in the current plane (and of the same tag)
                // contains the cuboid in the prev plane

                // case that the current cuboid does not contain the prev cuboid
                else if (!isAContainsB(currentPlane.begin()->first, key))
                {
                    // std::cout << "the current cuboid does not contain the prev cuboid" << std::endl;
                    // std::cout << "current cuboid: " << currentPlane.begin()->first.tag << ", topLeft( " << currentPlane.begin()->first.topLeft.x << ", " << currentPlane.begin()->first.topLeft.y << "),( " << currentPlane.begin()->first.bottomRight.x << " " << currentPlane.begin()->first.bottomRight.y << ")" << std::endl;
                    // std::cout << "prev cuboid: " << key.tag << ", topLeft( " << key.topLeft.x << ", " << key.topLeft.y << "),( " << key.bottomRight.x << " " << key.bottomRight.y << ")" << std::endl;
                    // push the cuboid into the output tasks
                    GlobalVars::outputTasks.push(it->second);
                    // remove the cuboid from the prev plane
                    it = prevPlane.erase(it);
                }

                // case that the current cuboid contains the prev cuboid

                else
                {
                    // get the next plane
                    std::map<CuboidKey, Cuboid> nextPlane;
                    transformToMap(planes[z + 1], nextPlane);
                    // retrieve all the cuboids from prev and next that are in the same area
                    std::map<CuboidKey, Cuboid> cuboidsFromPrevPlane;
                    std::map<CuboidKey, Cuboid> cuboidsFromNextPlane;
                    CuboidsInSameArea(prevPlane, cuboidsFromPrevPlane, nextPlane, cuboidsFromNextPlane, key);

                    // try to merge the cuboids in the same area
                    int originalSize=cuboidsFromPrevPlane.size()+cuboidsFromNextPlane.size()+1;
                    std::set<CuboidKey> dividedCuboids;
                    if (tryMerge(cuboidsFromPrevPlane,cuboidsFromNextPlane, key,dividedCuboids)<originalSize){
                        //divide the current cuboid into smaller cuboids and push them into the current plane
                        Cuboid currentCuboid=currentPlane[key];
                        for(auto it=dividedCuboids.begin();it!=dividedCuboids.end();it++){
                            Cuboid cuboid = Cuboid(currentCuboid.blockX, currentCuboid.blockY, currentCuboid.blockZ, it->topLeft.x, it->topLeft.y, currentCuboid.cuboidZ, it->bottomRight.x - it->topLeft.x + 1, it->bottomRight.y - it->topLeft.y + 1, currentCuboid.depth, currentCuboid.tag);
                            currentPlane[*it] = cuboid;
                        }
                        currentPlane.erase(key);
                    }
                }
            }
            // mergedPlane is the current plane
        }

        // if there are cuboids left in the current plane, push them into the merged plane
        for (auto it = currentPlane.begin(); it != currentPlane.end();)
        {
            std::cout << "push the cuboid in the current plane into the merged plane" << std::endl;
            mergedPlane[it->first] = it->second;
            it = currentPlane.erase(it);
        }
        std::cout << "reassign the merged plane to the prev plane" << std::endl;
        // reassign the merged plane to the prev plane
        prevPlane = mergedPlane;
    }

    for (auto it = prevPlane.begin(); it != prevPlane.end();)
    {
        std::cout << "end of loop" << std::endl;
        std::cout << "push the cuboid in the prev plane into the output tasks" << std::endl;
        GlobalVars::outputTasks.push(it->second);
        it = prevPlane.erase(it);
    }
}

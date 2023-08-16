#ifndef CUBOID_H
#define CUBOID_H

class Cuboid
{
public:
    Cuboid();
    Cuboid(int blockX, int blockY, int blockZ, int cuboidX, int cuboidY, int cuboidZ, int width, int height, int depth, char tag);
    int blockX;
    int blockY;
    int blockZ;
    int cuboidX;
    int cuboidY;
    int cuboidZ;
    int width;
    int height;
    int depth;
    char tag;
};

#endif
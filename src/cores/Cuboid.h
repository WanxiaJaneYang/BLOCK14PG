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

    int getCuboidX() const { return cuboidX; }
    int getCuboidY() const { return cuboidY; }
    int getCuboidZ() const { return cuboidZ; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getDepth() const { return depth; }
    char getTag() const { return tag; }
};

#endif
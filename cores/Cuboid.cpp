#include "Cuboid.h"

// default constructor
Cuboid::Cuboid()
{
    this->blockX = 0;
    this->blockY = 0;
    this->blockZ = 0;
    this->cuboidX = 0;
    this->cuboidY = 0;
    this->cuboidZ = 0;
    this->width = 0;
    this->height = 0;
    this->depth = 0;
    this->tag = ' ';
}

// overloaded constructor
Cuboid::Cuboid(int blockX, int blockY, int blockZ, int cuboidX, int cuboidY, int cuboidZ, int width, int height, int depth, char tag)
{
    this->blockX = blockX;
    this->blockY = blockY;
    this->blockZ = blockZ;
    this->cuboidX = cuboidX;
    this->cuboidY = cuboidY;
    this->cuboidZ = cuboidZ;
    this->width = width;
    this->height = height;
    this->depth = depth;
    this->tag = tag;
}
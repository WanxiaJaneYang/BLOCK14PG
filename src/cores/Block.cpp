#include "Block.h"

// constructor
Block::Block(int x, int y, int z)
{
    this->x=x;
    this->y=y;
    this->z=z;
}

// get x
int Block::getX() const
{
    return this->x;
}

// get y
int Block::getY() const
{
    return this->y;
}

// get z
int Block::getZ() const
{
    return this->z;
}

// set x
void Block::setX(int x)
{
    this->x = x;
}

// set y
void Block::setY(int y)
{
    this->y = y;
}

// set z
void Block::setZ(int z)
{
    this->z = z;
}

// set data
void Block::setData(const std::vector<std::vector<std::vector<char>>> &data)
{
    this->data = data;
}

// get data
std::vector<std::vector<std::vector<char>>> Block::getData() const
{
    return this->data;
}

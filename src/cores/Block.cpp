#include "Block.h"
#include <iostream>

// constructor
Block::Block() : x(0), y(0), z(0) {}

Block::Block(int x, int y, int z)
{
    this->x=x;
    this->y=y;
    this->z=z;
}

// get x
int Block::getX() const
{
    return x;
}

// get y
int Block::getY() const
{
    return y;
}

// get z
int Block::getZ() const
{
    return z;
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
    return data;
}

bool Block::isEmpty() const
{
    return data.empty();
}


// Method to check if the block is filled
bool Block::isFull(int height, int depth) const
{
    return !data.empty() && data.back().size() == height && data.size() == depth;
}

// Method to fill the block
void Block::fillBlock(int height, int depth, const std::vector<char> inputData)
{
    if (!Block::isFull(height, depth))
    {
        // Add a new slice if necessary
        if (data.empty() || data.back().size() == height)
        {
            data.push_back(std::vector<std::vector<char>>());
            data.back().reserve(height);
        }

        // Fill the data in the current slice
        data.back().push_back(inputData);
    }
}

void Block::printBlock() const
{
    std::cout << "[" << x << ", " << y << ", " << z << "]" << std::endl;

    for (const auto &outer : data)
    {
        for (const auto &inner : outer)
        {
            for (char c : inner)
            {
                std::cout << c << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
}
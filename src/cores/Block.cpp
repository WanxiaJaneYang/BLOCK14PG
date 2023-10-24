#include "Block.h"
#include <iostream>

// Default constructor
Block::Block() : x(0), y(0), z(0) {}

// Overloaded constructor
Block::Block(int x, int y, int z, int id)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->id = id;
}
Block::Block(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

// Get x
int Block::getX() const
{
    return x;
}

// Get y
int Block::getY() const
{
    return y;
}

// Get z
int Block::getZ() const
{
    return z;
}
int Block::getId() const { return id; }

void Block::setId(int id) { this->id = id; }
// Set x
void Block::setX(int x)
{
    this->x = x;
}

// Set y
void Block::setY(int y)
{
    this->y = y;
}

// Set z
void Block::setZ(int z)
{
    this->z = z;
}

// Set data
void Block::setData(const std::vector<std::vector<std::vector<char>>> &data)
{
    this->data = data;
}

// Get data
std::vector<std::vector<std::vector<char>>> Block::getData() const
{
    return data;
}

// Method to check if the block is empty
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
void Block::fillBlock(int height, int depth, const std::vector<char> &inputData)
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
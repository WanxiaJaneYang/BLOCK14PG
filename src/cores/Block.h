#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

class Block
{
public:
    Block();
    Block(int x, int y, int z);

    // Accessors and Mutators
    int getX() const;
    int getY() const;
    int getZ() const;

    void setX(int x);
    void setY(int y);
    void setZ(int z);

    // Methods to handle the 3D data
    void setData(const std::vector<std::vector<std::vector<char>>> &data);
    std::vector<std::vector<std::vector<char>>> getData() const;

    // Method to check if the block is empty
    bool isEmpty() const;

    // Method to check if the block is filled
    bool isFull(int height) const;

    // Method to fill the block
    void fillBlock(int height, const std::vector<char> inputData);

private:
    int x;
    int y;
    int z;
    std::vector<std::vector<std::vector<char>>> data;
};

#endif

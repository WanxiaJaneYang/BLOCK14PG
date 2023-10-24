#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

class Block
{
public:
    int id;

    Block();
    Block(int x, int y, int z, int id);
    Block(int x, int y, int z);

    // Accessors and Mutators
    int getX() const;
    int getY() const;
    int getZ() const;
    int getId() const;
    void setId(int id);
    void setX(int x);
    void setY(int y);
    void setZ(int z);

    // Methods to handle the 3D data
    void setData(const std::vector<std::vector<std::vector<char>>> &data);
    std::vector<std::vector<std::vector<char>>> getData() const;

    // Method to check if the block is empty
    bool isEmpty() const;

    // Method to check if the block is filled
    bool isFull(int height, int depth) const;

    // Method to fill the block
    void fillBlock(int height, int depth, const std::vector<char> &inputData);

private:
    int x;
    int y;
    int z;
    std::vector<std::vector<std::vector<char>>> data;
};

#endif

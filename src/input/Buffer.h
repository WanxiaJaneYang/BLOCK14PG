#include <vector>
#include "../cores/Block.h"
#ifndef BUFFER_H
#define BUFFER_H

class Buffer
{
private:
    std::vector<Block> tasks;

public:
    Buffer();
    // Method to get size of buffer
    int size();
    // Method to push block into buffer
    void push(const Block &block);
    // Method to pop block into buffer
    bool pop(Block &block);
    // Method to fill empty block into buffer with size
    void resize(int size);
    // Method to get block reference from buffer with index
    Block &getFromIndex(int index);
    // Destructor
    virtual ~Buffer();
};

#endif

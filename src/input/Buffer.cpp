#include "Buffer.h"
#include <iostream>

Buffer::Buffer()
{
    // Constructor
}

Buffer::~Buffer()
{
    // Destructor
}

// Method to get size of buffer
int Buffer::size()
{
    return tasks.size();
}

// Method to push block into buffer
void Buffer::push(const Block &block)
{
    tasks.push_back(block);
}

// Method to pop block into buffer
bool Buffer::pop(Block &block)
{
    if (tasks.empty())
    {
        return false;
    }
    block = tasks.back();
    tasks.pop_back();
    return true;
}

// Method to get block reference from buffer with index
Block &Buffer::getFromIndex(int index)
{
    if (tasks.size() < (index+1))
    {
        tasks.push_back(Block());
    }

        return tasks[index];
}
#include "Buffer.h"
#include <iostream>

Buffer::Buffer()
{
    // constructor
}

Buffer::~Buffer()
{
    // destructor
}

int Buffer::size()
{
    return tasks.size();
}

void Buffer::push(const Block &block)
{
    tasks.push_back(block);
}

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

void Buffer::resize(int size)
{
    tasks.resize(size, Block());
}

Block &Buffer::getFromIndex(int index)
{
    return tasks[index];
}

void Buffer::printTasks() const
{
    int count = 0;
    for (const Block &block : tasks)
    {
        count++;
        std::cout << "Block" << count << std::endl;
        block.printBlock();
    }
}
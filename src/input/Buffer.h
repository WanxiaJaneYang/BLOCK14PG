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
    int size();
    void push(const Block &block);
    bool pop(Block &block);
    void resize(int size);
    Block &getFromIndex(int index);
    void printTasks() const;
    virtual ~Buffer();
};

#endif

#include <vector>
// #include <mutex>
#include "Block.h"
#ifndef SAFEINPUTTASKS_H
#define SAFEINPUTTASKS_H

class SafeInputTasks
{
private:
    std::vector<Block> tasks;
    // std::mutex mtx;

public:
    SafeInputTasks();
    int size();
    void push(const Block &block);
    bool pop(Block &block);
    virtual ~SafeInputTasks();
};

#endif

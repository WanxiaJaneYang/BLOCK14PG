#include <vector>
#include <mutex>
#include <deque>
#include "Block.h"
#ifndef SAFEINPUTTASKS_H
#define SAFEINPUTTASKS_H

class SafeInputTasks
{
#ifdef TEST
    public: std::deque<Block> tasks;
#else
    private: std::deque<Block> tasks;
#endif
    std::mutex mtx;

public:
    SafeInputTasks();
    int size();
    void push(const Block &block);
    bool pop(Block &block);
    virtual ~SafeInputTasks();
};

#endif

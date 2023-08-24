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
    void resize(int size);
    Block& getFromIndex(int index);
    void printTasks() const;
    std::string writeTasks() const;
    void clearTasks();
    virtual ~SafeInputTasks();
};

#endif

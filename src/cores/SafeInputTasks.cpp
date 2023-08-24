#include "SafeInputTasks.h"
#include <iostream>
#include <sstream>
#include <string>

SafeInputTasks::SafeInputTasks()
{
    // constructor
}

SafeInputTasks::~SafeInputTasks()
{
    // destructor
}

int SafeInputTasks::size()
{
    // std::lock_guard<std::mutex> lock(mtx);
    return tasks.size();
}

void SafeInputTasks::push(const Block &block)
{
    // std::lock_guard<std::mutex> lock(mtx);
    tasks.push_back(block);
}

bool SafeInputTasks::pop(Block &block)
{
    // std::lock_guard<std::mutex> lock(mtx);
    if (tasks.empty())
    {
        return false;
    }
    block = tasks.back();
    tasks.pop_back();
    return true;
}

void SafeInputTasks::resize(int size)
{
    tasks.resize(size, Block());
}

Block& SafeInputTasks::getFromIndex(int index)
{
    return tasks[index];
}

void SafeInputTasks::printTasks() const
{
    int count = 0;
    for (const Block &block: tasks)
    {
        count++;
        std::cout << "Block" << count << std::endl;
        block.printBlock();
    }
}

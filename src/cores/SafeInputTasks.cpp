#include "SafeInputTasks.h"

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
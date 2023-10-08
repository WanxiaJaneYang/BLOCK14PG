#include "SafeOutputTasks.h"

SafeOutputTasks::SafeOutputTasks()
{
    // ctor
}

SafeOutputTasks::~SafeOutputTasks()
{
    // dtor
}

int SafeOutputTasks::size()
{
    std::lock_guard<std::mutex> lock(mtx);
    int size = tasks.size();
    return size;
}

void SafeOutputTasks::push(const Cuboid &cuboid)
{
    std::lock_guard<std::mutex> lock(mtx);  // Locks the mutex
    tasks.push_back(cuboid);
}

bool SafeOutputTasks::pop(Cuboid &cuboid)
{
    std::lock_guard<std::mutex> lock(mtx);  // Locks the mutex
    if (tasks.empty())
    {
        return false;
    }
    cuboid = tasks.back();
    tasks.pop_back();
    return true;
}

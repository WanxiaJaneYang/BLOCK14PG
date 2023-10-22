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

void SafeOutputTasks::push(const std::deque<std::deque<Cuboid>>& cuboids)
{
    std::lock_guard<std::mutex> lock(mtx);  // Locks the mutex
    tasks.push_back(cuboids);
}

bool SafeOutputTasks::pop(std::deque<std::deque<Cuboid>>& cuboids)
{
    std::lock_guard<std::mutex> lock(mtx);  // Locks the mutex
    if (tasks.empty())
    {
        return false;
    }
    cuboids = tasks.back();
    tasks.pop_back();
    return true;
}

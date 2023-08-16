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
    // mtx.lock();
    int size = tasks.size();
    // mtx.unlock();
    return size;
}

void SafeOutputTasks::push(const Cuboid &cuboid)
{
    // mtx.lock();
    tasks.push_back(cuboid);
    // mtx.unlock();
}

bool SafeOutputTasks::pop(Cuboid &cuboid)
{
    // mtx.lock();
    if (tasks.empty())
    {
        // mtx.unlock();
        return false;
    }
    cuboid = tasks.back();
    tasks.pop_back();
    // mtx.unlock();
    return true;
}
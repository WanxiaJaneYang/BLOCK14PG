#include <vector>
// #include<mutex>
#include "Cuboid.h"
#ifndef SAFEOUTPUTTASKS_H
#define SAFEOUTPUTTASKS_H

class SafeOutputTasks
{
private:
    std::vector<Cuboid> tasks;
    // std::mutex mtx;
public:
    SafeOutputTasks();
    int size();
    void push(const Cuboid &cuboid);
    bool pop(Cuboid &cuboid);
    virtual ~SafeOutputTasks();
};
#endif
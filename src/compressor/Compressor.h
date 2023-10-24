#include <deque>
#include "../cores/Block.h"
#include "../cores/Cuboid.h"
#ifndef COMPRESSOR_H
#define COMPRESSOR_H

void compress();
std::deque<std::deque<std::deque<Cuboid>>> lineCompress(Block &block);
std::deque<std::deque<Cuboid>> planeCompress(std::deque<std::deque<std::deque<Cuboid>>> &compressedLines);

#endif
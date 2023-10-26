#include <deque>
#include "../cores/Block.h"
#include "../cores/Cuboid.h"
#ifndef COMPRESSOR_H
#define COMPRESSOR_H

void compress();
void lineCompress(Block &block,int thread);
void startLineCompressor2(Block &block);
// std::deque<std::deque<Cuboid>> planeCompress(std::deque<std::deque<std::deque<Cuboid>>> &compressedLines);

#endif
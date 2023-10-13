#include <deque>
#include "../cores/Block.h"
#include "../cores/Cuboid.h"
#include "./BlockCompress.h"
#include <map>
#ifndef COMPRESSOR_H
#define COMPRESSOR_H

void compress();
std::deque<std::deque<std::deque<Cuboid>>> lineCompress(Block &block);
<<<<<<< HEAD
void planeCompress(std::deque<std::deque<std::deque<Cuboid>>> &compressedLines);

=======
std::deque<std::deque<Cuboid>> planeCompress(std::deque<std::deque<std::deque<Cuboid>>> &compressedLines);
>>>>>>> origin/183-3d-compression-improved
#endif
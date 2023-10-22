#ifndef CHUNK_H
#define CHUNK_H

#include <iostream>
#include <vector>
#include <ostream>
#include <unordered_map>
#include <string>

class Chunk
{
public:
    std::vector<std::vector<std::vector<char>>> matrix;
    static std::unordered_map<char,std::string> labelMapping; 
public:
    // Constructor
    Chunk(int dimX, int dimY, int dimZ, char initialValue);
    int size();

    // Function to change characters in a specified 3D rectangle
    void changeRectangle(int x, int y, int z, int length, int width, int height, std::string newLabel);
};

#endif // CHUNK_H

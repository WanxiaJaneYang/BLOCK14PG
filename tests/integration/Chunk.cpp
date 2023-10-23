#include "Chunk.h"
#include <iostream>
#include <vector>

Chunk::Chunk(int dimX, int dimY, int dimZ, char initialValue)
{
    matrix.resize(dimZ, std::vector<std::vector<char>>(dimY, std::vector<char>(dimX, initialValue)));
}

std::unordered_map<char, std::string> Chunk::labelMapping = {
    {'o', "air"},
    {'B', "basement"},
    {'C', "cover"},
    {'f', "sd_1"},
    {'g', "sd_2"},
    {'h', "sd_3"},
    {'i', "sd_4"},
    {'j', "sd_5"},
    {'k', "sd_6"},
    {'l', "sd_7"},
    {'m', "sd_8"},
    {'n', "sd_9"},
    {'E', "sill_E"},
    {'W', "sill_W"}
};


int Chunk::size()
{
    return matrix.size();
}

void Chunk::changeRectangle(int x, int y, int z, int length, int width, int height, std::string newLabel)
{
    char shorthand;
    newLabel.erase(newLabel.find_last_not_of(" \n\r\t") + 1);

    for (const auto &pair : labelMapping)
    {
        // std::cerr << "seeking shorthand---- " << std::endl;
        // std::cerr << "Received label: " << newLabel << std::endl;
        if (newLabel == pair.second)
        {
            shorthand = pair.first;
            // std::cerr << "shorthand found: " << shorthand << std::endl;
            break;
        }
    }
    for (int depth = z; depth < z + height && depth < matrix.size(); depth++)
    {
        for (int row = y; row < y + width && row < matrix[depth].size(); row++)
        {
            for (int col = x; col < x + length && col < matrix[depth][row].size(); col++)
            {
                matrix[depth][row][col] = shorthand;
            }
        }
    }
}

// std::unordered_map<char, std::string> Chunk::labelMapping = {
//     {'e', "NSW"},
//     {'n', "NT"},
//     {'q', "QLD"},
//     {'s', "SA"},
//     {'t', "TAS"},
//     {'v', "VIC"},
//     {'w', "WA"},
//     {'o', "sea"}};
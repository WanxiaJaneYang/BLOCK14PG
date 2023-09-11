#include "Helper.h"

// Utility function to get all input files from a directory
std::vector<std::string> listInputFiles(const std::string &directory)
{
    std::vector<std::string> files;
    for (const auto &entry : std::filesystem::directory_iterator(directory))
    {

        if (entry.path().extension() == ".txt" && entry.path().string().find("_case.txt") != std::string::npos)
        {
            std::cout << entry.path().string() << std::endl;
            files.push_back(entry.path().string());
        }
    }
    return files;
}

Block createBlockFromInputFile(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    std::string firstLine;
    std::getline(file, firstLine);
    std::stringstream ss(firstLine);
    char comma;

    int blockX, blockY, blockZ;
    ss >> blockX >> comma >> blockY >> comma >> blockZ >> comma >> GlobalVars::width >> comma >> GlobalVars::height >> comma >> GlobalVars::depth;

    if (ss.fail() || comma != ',')
    {
        throw std::runtime_error("Invalid format in the first line of the file: " + filePath);
    }

    Block newBlock(blockX, blockY, blockZ);

    std::vector<std::vector<std::vector<char>>> blockData;

    for (int depth = 0; depth < GlobalVars::depth; depth++)
    {
        std::vector<std::vector<char>> matrix;
        std::string line;

        while (std::getline(file, line))
        {
            // If we encounter an empty line, break and proceed to the next matrix/plane
            if (line.empty())
            {
                break;
            }
            std::vector<char> row(line.begin(), line.end());
            matrix.push_back(row);
        }

        // Ensure that we've read the expected number of rows for this plane
        if (matrix.size() != GlobalVars::height)
        {
            throw std::runtime_error("Unexpected number of rows for plane: " + std::to_string(depth));
        }

        blockData.push_back(matrix);
    }

    newBlock.setData(blockData);

    return newBlock;
}

std::string writeCompressedResult(const std::deque<std::deque<std::deque<Cuboid>>> &compressedResult)
{
    std::stringstream output;

    for (const auto &plane : compressedResult)
    {
        for (const auto &line : plane)
        {
            for (const auto &cuboid : line)
            {
                // Print each Cuboid's details in the format:
                output << cuboid.getBlockX() << ", ";
                output << cuboid.getBlockY() << ", ";
                output << cuboid.getBlockZ() << ", ";
                output << cuboid.getCuboidX() << ", ";
                output << cuboid.getCuboidY() << ", ";
                output << cuboid.getCuboidZ() << ", ";
                output << cuboid.getWidth() << ", ";
                output << cuboid.getHeight() << ", ";
                output << cuboid.getDepth() << ", ";
                output << cuboid.getTag();
                output << "\n"; // Newline after each Cuboid
            }
        }
    }
    return output.str();
}

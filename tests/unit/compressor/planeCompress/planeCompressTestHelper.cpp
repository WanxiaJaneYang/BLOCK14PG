#include "planeCompressTestHelper.h"

// Utility function to get all input files from a directory
std::vector<std::string> listInputFiles(const std::string &directory)
{
    std::vector<std::string> files;
    for (const auto &entry : std::__fs::filesystem::directory_iterator(directory))
    {
        if (entry.path().extension() == ".txt" && entry.path().string().find("_case.txt") != std::string::npos)
        {
            std::cout << entry.path().string() << std::endl;
            files.push_back(entry.path().string());
        }
    }
    return files;
}

// Method to convert string to std::deque<std::deque<Cuboid>> as parameter of block compressor
std::deque<std::deque<std::deque<Cuboid>>> convertFileContentToLines(const std::string &fileContent)
{
    std::deque<std::deque<std::deque<Cuboid>>> blocks;
    std::deque<std::deque<Cuboid>> lines;
    std::deque<Cuboid> cuboids;

    std::istringstream iss(fileContent);
    std::string line;
    std::getline(iss, line);

    // get block coordinate
    int blockX, blockY, blockZ;
    std::istringstream blockStream(line);
    blockStream >> blockX;
    blockStream.ignore();
    blockStream >> blockY;
    blockStream.ignore();
    blockStream >> blockZ;

    int emptyLineCount = 0;

    while (std::getline(iss, line))
    {
        if (line.empty())
        {
            emptyLineCount++;

            // if there is only one black line, means change line
            if (emptyLineCount == 1 && !cuboids.empty())
            {
                lines.push_back(cuboids);
                cuboids.clear();
            }
            // if there is two black line, means change layer
            else if (emptyLineCount == 2)
            {
                if (!lines.empty())
                {
                    blocks.push_back(lines);
                    lines.clear();
                }
                emptyLineCount = 0;
            }
        }
        else
        {
            emptyLineCount = 0;

            std::istringstream cuboidStream(line);
            int cuboidX, cuboidY, cuboidZ, width, height, depth;
            char tag;

            cuboidStream >> cuboidX;
            cuboidStream.ignore();
            cuboidStream >> cuboidY;
            cuboidStream.ignore();
            cuboidStream >> cuboidZ;
            cuboidStream.ignore();
            cuboidStream >> width;
            cuboidStream.ignore();
            cuboidStream >> height;
            cuboidStream.ignore();
            cuboidStream >> depth;
            cuboidStream.ignore();
            cuboidStream >> tag;

            // instance a  cuboid
            Cuboid cuboid(blockX, blockY, blockZ, cuboidX, cuboidY, cuboidZ, width, height, depth, tag);
            cuboids.push_back(cuboid);
        }
    }

    if (!cuboids.empty())
    {
        lines.push_back(cuboids);
    }
    if (!lines.empty())
    {
        blocks.push_back(lines);
    }

    return blocks;
}

// Utility function to write the block into a string
std::string writeContentOfCuboid(const Cuboid &cuboid)
{
    std::ostringstream oss;

    oss << cuboid.cuboidX << ",";
    oss << cuboid.cuboidY << ",";
    oss << cuboid.cuboidZ << ",";
    oss << cuboid.width << ",";
    oss << cuboid.height << ",";
    oss << cuboid.depth << ",";
    oss << cuboid.tag << "\n";

    return oss.str();
}

// Method to write outcome of block compress
std::string writeReadContent(const std::deque<std::deque<Cuboid>> &planes)
{
    std::ostringstream oss;

    for (const auto &plane : planes)
    {
        for (const auto &cuboid : plane)
        {
            oss << writeContentOfCuboid(cuboid);
        }
        // Append a blank line to separate planes
        oss << "\n";
    }

    return oss.str();
}

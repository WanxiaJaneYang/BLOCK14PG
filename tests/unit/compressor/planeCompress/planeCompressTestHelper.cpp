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
    blockStream.ignore();
    blockStream >> GlobalVars::width;
    blockStream.ignore();
    blockStream >> GlobalVars::height;
    blockStream.ignore();
    blockStream >> GlobalVars::depth;

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

    oss << cuboid.blockX << ",";
    oss << cuboid.blockY << ",";
    oss << cuboid.blockZ << ",";
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
        // new cotainer for cuboids
        std::deque<Cuboid> sortedCuboids = plane;

        // sort cuboids in the plane
        std::sort(sortedCuboids.begin(), sortedCuboids.end(), [](const Cuboid &a, const Cuboid &b)
        {
            if (a.cuboidX != b.cuboidX) return a.cuboidX < b.cuboidX;
            if (a.cuboidY != b.cuboidY) return a.cuboidY < b.cuboidY;
            if (a.cuboidZ != b.cuboidZ) return a.cuboidZ < b.cuboidZ;
            if (a.width != b.width) return a.width < b.width;
            if (a.height != b.height) return a.height < b.height;
            if (a.depth != b.depth) return a.depth < b.depth;
            return a.tag < b.tag; 
        });

        // write into oss
        for (const auto &cuboid : sortedCuboids)
        {
            oss << writeContentOfCuboid(cuboid);
        }

        // black line
        oss << "\n";
    }

    return oss.str();
}

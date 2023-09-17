#include "blockCompressTestHelper.h"

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

// Method to convert string to std::deque<std::deque<Cuboid>> as parameter of block compressor
std::deque<std::deque<Cuboid>> convertFileContentToPlanes(const std::string &fileContent)
{
    std::deque<std::deque<Cuboid>> planes;
    std::deque<Cuboid> currentPlane;

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

    while (std::getline(iss, line))
    {
        // If the line is blank, it indicates the end of the current plane.
        if (line.empty())
        {
            if (!currentPlane.empty())
            {
                planes.push_back(currentPlane);
                currentPlane.clear();
            }
            continue;
        }

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
        currentPlane.push_back(cuboid);
    }

    // Add the last plane if it's not empty
    if (!currentPlane.empty())
    {
        planes.push_back(currentPlane);
    }

    return planes;
}

// Utility function to write tasks into a string
std::string writeContentOfTasks(SafeOutputTasks &tasks)
{
    std::ostringstream oss;
    // new cotainer for cuboids
    std::vector<Cuboid> sortedCuboids = tasks.tasks;

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

    return oss.str();
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
std::string writeReadContent()
{
    // Convert the data stored into a string
    std::ostringstream oss;

    // Add blocks in tasks to the string
    oss << writeContentOfTasks(GlobalVars::outputTasks);

    clearTasks(GlobalVars::outputTasks); // important for bulk tests

    return oss.str();
}

// clears the tasks vector
void clearTasks(SafeOutputTasks &tasks)
{
    tasks.tasks.clear();
}

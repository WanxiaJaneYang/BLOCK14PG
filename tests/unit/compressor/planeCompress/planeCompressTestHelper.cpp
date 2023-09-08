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
    std::deque<std::deque<std::deque<Cuboid>>> lines;
    std::deque<std::deque<Cuboid>> currentPlane;
    std::deque<Cuboid> currentLine;

    std::istringstream iss(fileContent);
    std::string line;

    while (std::getline(iss, line))
    {
        // If the line is blank, it indicates the end of the current line and possibly the plane.
        if (line.empty())
        {
            if (!currentLine.empty())
            {
                currentPlane.push_back(currentLine);
                currentLine.clear();
            }

            if (!currentPlane.empty())
            {
                lines.push_back(currentPlane);
                currentPlane.clear();
            }
            continue;
        }

        // Handle line to populate a Cuboid object
        std::istringstream lineStream(line);
        std::string token;
        Cuboid cuboid;

        std::getline(lineStream, token, ',');
        cuboid.blockX = std::stoi(token);
        std::getline(lineStream, token, ',');
        cuboid.blockY = std::stoi(token);
        std::getline(lineStream, token, ',');
        cuboid.blockZ = std::stoi(token);
        std::getline(lineStream, token, ',');
        cuboid.cuboidX = std::stoi(token);
        std::getline(lineStream, token, ',');
        cuboid.cuboidY = std::stoi(token);
        std::getline(lineStream, token, ',');
        cuboid.cuboidZ = std::stoi(token);
        std::getline(lineStream, token, ',');
        cuboid.width = std::stoi(token);
        std::getline(lineStream, token, ',');
        cuboid.height = std::stoi(token);
        std::getline(lineStream, token, ',');
        cuboid.depth = std::stoi(token);
        std::getline(lineStream, token, ',');
        cuboid.tag = std::stoi(token);

        // Add Cuboid to currentLine
        currentLine.push_back(cuboid);
    }

    // Add the last line and plane if they're not empty
    if (!currentLine.empty())
    {
        currentPlane.push_back(currentLine);
    }
    if (!currentPlane.empty())
    {
        lines.push_back(currentPlane);
    }

    return lines;
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
    oss << cuboid.tag << "\r\n";

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
        oss << "\r\n";
    }

    return oss.str();
}

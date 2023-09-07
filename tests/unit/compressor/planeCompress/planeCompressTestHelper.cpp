#include "blockCompressTestHelper.h"

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
std::deque<std::deque<Cuboid>> convertFileContentToPlanes(const std::string &fileContent)
{
    std::deque<std::deque<Cuboid>> planes;
    std::deque<Cuboid> currentPlane;

    std::istringstream iss(fileContent);
    std::string line;

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

        // Add Cuboid to currentPlane
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
    for (int i = 0; i < tasks.size(); ++i)
    {
        Cuboid &cuboid = tasks.tasks[i];
        // Assuming Block has a method that returns a string representation
        oss << "\r\n"
            << "Cuboid" << (i + 1) << writeContentOfCuboid(cuboid);
    }
    return oss.str();
}

// Utility function to write the block into a string
std::string writeContentOfCuboid(Cuboid &cuboid)
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

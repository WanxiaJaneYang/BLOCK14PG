#include "readInput.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

void readInput()
{
    std::string line;

    // Get the first line
    std::getline(in, line);
    std::istringstream iss(line);
    int mapWidth, mapHeight, mapDepth;
    char comma;

    // Collect size parameters
    iss >> mapWidth >> comma >> mapHeight >> comma >> mapDepth >> comma >> GlobalVars::width >> comma >> GlobalVars::height >> comma >> GlobalVars::depth;

    // Get label pairs lines and save them into tagTable
    while (std::getline(in, line))
    {
        if (line.find(',') == std::string::npos)
            break;

        std::istringstream ss(line);
        char key;
        std::string value;

        ss >> key >> comma;
        std::getline(ss, value, ',');
        GlobalVars::tagTable[key] = value;
    }

    // Collecting parent size blocks
    int numX = mapWidth / GlobalVars::width;
    int numY = mapHeight / GlobalVars::height;

    Buffer bufferLst;

    // Define counters
    int lineCount = 0;
    int rowCount = 0;
    int zCoord = 0;
    int index = -1;

    // Start to read block
    while (std::getline(in, line))
    {
        // Removing any newline or carriage return characters at the end of line
        while (!line.empty() && (line.back() == '\n' || line.back() == '\r'))
        {
            line.pop_back();
        }

        // If the line is empty, which indicates a new slice
        if (line.empty())
        {
            zCoord++;

            // This can indicates if need go to next buffer block
            if ((zCoord + 1) % GlobalVars::depth != 1 && GlobalVars::depth != 1)
            {
                index -= numX * numY;
            }

            // New slice, line counter is reset to 0
            lineCount = 0;
            continue;
        }

        // Processing a new line
        rowCount = 0;

        // For collecting one bar (width=parentSize width, height=1, depth=1)
        std::vector<char> inputDataTemp;

        // Processing each point
        for (char e : line)
        {
            inputDataTemp.push_back(e);
            rowCount++;

            // Check if need to change buffer block
            if (rowCount % GlobalVars::width == 1 || GlobalVars::width == 1)
            {
                index++;
            }

            Block &blockRef = bufferLst.getFromIndex(index);

            // Check if the point is the first point of the buffer block
            if (blockRef.isEmpty() && ((rowCount % GlobalVars::width == 1 && GlobalVars::width != 1) || GlobalVars::width == 1))
            {
                // get coordinate
                int xCoord = rowCount - 1;
                int yCoord = lineCount;

                // Save into buffer block
                blockRef.setX(xCoord);
                blockRef.setY(yCoord);
                blockRef.setZ(zCoord);
            }

            // Check if bar is full
            if (inputDataTemp.size() == GlobalVars::width)
            {

                blockRef.fillBlock(GlobalVars::height, GlobalVars::depth, inputDataTemp);
                inputDataTemp.clear();
            }

            // Check if the buffer block is full
            if (rowCount % GlobalVars::width == 0 && (lineCount + 1) % GlobalVars::height == 0 && (zCoord + 1) % GlobalVars::depth == 0)
            {
                // Store the full bloack of buffer into GlobalVars::processTasks
                GlobalVars::processTasks.push(blockRef);

                // Pop full block from buffer list and decrease index by 1
                bufferLst.tasks.erase(bufferLst.tasks.begin() + index);
                index--;
            }
        }

        lineCount++;

        // Check if need to change buffer block
        if ((lineCount + 1) % GlobalVars::height != 1 && GlobalVars::height != 1)
        {
            index -= numX;
        }
    }
}
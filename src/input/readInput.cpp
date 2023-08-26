#include "readInput.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

void readInput()
{
    // Read input file using the file name stored in GlobalVars::inputFileName
    GlobalVars::inputFileName = "./input/test case.csv";

    std::ifstream file(GlobalVars::inputFileName);

    std::string line;

    // Get the first line
    std::getline(file, line);
    std::istringstream iss(line);
    int big_width, big_height, big_depth;
    char comma;

    // Collect size parameters
    iss >> big_width >> comma >> big_height >> comma >> big_depth >> comma >> GlobalVars::width >> comma >> GlobalVars::height >> comma >> GlobalVars::depth;

    // Get label pairs lines and save them into tagTable
    while (std::getline(file, line))
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
    int num_x = big_width / GlobalVars::width;
    int num_y = big_height / GlobalVars::height;
    int num_z = big_depth / GlobalVars::depth;
    int total_blocks = num_x * num_y * num_z;

    SafeInputTasks buffer_lst;
    
    // Initialize buffer list with blocks
    buffer_lst.resize(total_blocks);

    // Define counters 
    int line_count = 0;
    int row_count = 0;
    int z_coord = 0;
    int index = -1;

    // Start to read block
    while (std::getline(file, line))
    {
        // Removing any newline or carriage return characters at the end of line
        while (!line.empty() && (line.back() == '\n' || line.back() == '\r'))
        {
            line.pop_back();
        }
        
        // If the line is empty, which indicates a new slice
        if (line.empty())
        {
            z_coord++;

            // This can indicates if need go to next buffer block
            if ((z_coord + 1) % GlobalVars::depth != 1)
            {
                index -= num_x * num_y;
            }

            // New slice, line counter is reset to 0
            line_count = 0;
            continue;
        }

        // Processing a new line
        row_count = 0;

        // For collecting one bar (width=parentSize width, height=1, depth=1)
        std::vector<char> inputDataTemp;

        // Processing each point
        for (char e : line)
        {
            inputDataTemp.push_back(e);
            row_count++;

            // Check if need to change buffer block 
            if (row_count % GlobalVars::width == 1)
            {
                index++;
            }

            Block &blockRef = buffer_lst.getFromIndex(index);

            // Check if bar is full
            if (inputDataTemp.size() == GlobalVars::width)
            {
                blockRef.fillBlock(GlobalVars::height, GlobalVars::depth, inputDataTemp);
                inputDataTemp.clear();
            }

            // Check if the point is the first point of the buffer block
            if (row_count % GlobalVars::width == 1 && blockRef.isEmpty())
            {
                // get coordinate
                int x_coord = row_count - 1;
                int y_coord = line_count;

                // Save into buffer block
                blockRef.setX(x_coord);
                blockRef.setY(y_coord);
                blockRef.setZ(z_coord);
            }

            // Check if the buffer block is full
            if (row_count % GlobalVars::width == 0 && (line_count + 1) % GlobalVars::height == 0 && (z_coord + 1) % GlobalVars::depth == 0)
            {
                // Store the full bloack of buffer into GlobalVars::processTasks
                GlobalVars::processTasks.push(blockRef);
            }
        }

        line_count++;

        // Check if need to change buffer block
        if ((line_count + 1) % GlobalVars::height != 1)
        {
            index -= num_x;
        }
    }

    file.close();
}

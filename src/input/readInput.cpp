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
    GlobalVars::inputFileName = "./input/input.txt";

    std::ifstream file(GlobalVars::inputFileName);

    if (!file)
    {
        std::cerr << "Unable to open file: " << GlobalVars::inputFileName << std::endl;
        return;                                                         
    }

    std::string line;

    // get first line
    std::getline(file, line);
    std::istringstream iss(line);
    int big_width,big_height,big_depth;
    char comma;
    // collect size parameters
    iss >> big_width >> comma >> big_height >> comma >> big_depth >> comma >> GlobalVars::width >> comma >> GlobalVars::height >> comma >> GlobalVars::depth;
    
    // get labels pairs lines
    while (std::getline(file, line))
    {
        if (line.find(',') == std::string::npos) break;
        std::istringstream ss(line);
        char key;
        std::string value;
        ss >> key >> comma;
        std::getline(ss, value, ',');
        GlobalVars::tagTable[key] = value;
    }

    //for testing print
    // std::cout << big_width << " "
    //           << big_height << " "
    //           << big_depth << " "
    //           << GlobalVars::width << " "
    //           << GlobalVars::height << " "
    //           << GlobalVars::depth << std::endl;

    // for (const auto &pair : GlobalVars::tagTable)
    // {
    //     std::cout << pair.first << " -> " << pair.second << std::endl;
    // }


    int num_x = big_width / GlobalVars::width;
    int num_y = big_height / GlobalVars::height;
    int num_z = big_depth / GlobalVars::depth;

    int total_blocks = num_x * num_y * num_z;

    SafeInputTasks buffer_lst;

    // initialize buffer list with blocks
    buffer_lst.resize(total_blocks);

    int line_count = 0; 
    int z_coord = 0;

    while (std::getline(file, line))
    {
        if (line.empty()) 
        {
            z_coord++;
            line_count = 0;
            continue;
        }

        int row_count = 0;
        std::vector<char> inputDataTemp;

        for (char e : line)
        {
            inputDataTemp.push_back(e);
            row_count++;

            if (inputDataTemp.size() == GlobalVars::width)
            {
                int index = getIndex(num_x, num_y, line_count, row_count, z_coord);
                Block &blockRef = buffer_lst.getFromIndex(index);

                blockRef.fillBlock(GlobalVars::height, inputDataTemp);
                inputDataTemp.clear();
            }
            
            if (row_count % GlobalVars::width == 1)
            {
                int x_coord = row_count-1;
                int y_coord = line_count;

                int index = getIndex(num_x, num_y, line_count, row_count, z_coord);
                Block &blockRef = buffer_lst.getFromIndex(index);

                if (blockRef.isEmpty())
                {
                    blockRef.setX(x_coord);
                    blockRef.setY(y_coord);
                    blockRef.setZ(z_coord);
                }
               
            }
        }

        line_count++;
    }
    // and store the data in GlobalVars::processTasks
    GlobalVars::processTasks = buffer_lst;

    file.close();
}

int getIndex(int num_x, int num_y, int line_count, int row_count, int z_coord)
{
    // calculate index of buffer
    int block_in_xy_plane = num_x * num_y;
    int y_offset = line_count / GlobalVars::height;
    int x_offset = row_count / GlobalVars::width;
    int index = z_coord * block_in_xy_plane + y_offset * num_x + x_offset;

    // if the block in buffer is empty, save the coordinate into the block
    return index;
}
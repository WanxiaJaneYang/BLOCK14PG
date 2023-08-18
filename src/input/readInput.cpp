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

    int num_x = big_width / GlobalVars::width;
    int num_y = big_height / GlobalVars::height;
    int num_z = big_depth / GlobalVars::depth;

    int total_blocks = num_x * num_y * num_z;
    
    SafeInputTasks buffer_lst;

    // initialize buffer list with blocks
    buffer_lst.resize(total_blocks);

    int line_count = 0;
    int row_count = 0;
    int z_coord = 0;
    int index = -1;

    while (std::getline(file, line))
    {
        // removing \n or \r at the end of line
        if (!line.empty() && (line.back() == '\n' || line.back() == '\r'))
        {
            line.pop_back();
        }

        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }

        // if the line is empty, which means new slice
        if (line.empty()) 
        {
            z_coord++;

            if ((z_coord + 1) % GlobalVars::depth == 1)
            {
                index++;
            } 
            else 
            {
                index -= num_x * num_y;
            }

            line_count = 0;
            continue;
        }
        
        // new line
        row_count = 0;
        std::vector<char> inputDataTemp;

        for (char e : line)
        {

            inputDataTemp.push_back(e);
            
            row_count++;

            if (row_count % GlobalVars::width == 1)
            {
                index++;
            }

            if (inputDataTemp.size() == GlobalVars::width)
            {

                Block &blockRef = buffer_lst.getFromIndex(index);

                blockRef.fillBlock(GlobalVars::height, GlobalVars::depth, inputDataTemp);

                inputDataTemp.clear();
            }

            Block &blockRef = buffer_lst.getFromIndex(index);

            if (row_count % GlobalVars::width == 1 && blockRef.isEmpty())
            {

                int x_coord = row_count-1;
                int y_coord = line_count;

                blockRef.setX(x_coord);
                blockRef.setY(y_coord);
                blockRef.setZ(z_coord);
               
            }
        }

        line_count++;

        if ((line_count+1) % GlobalVars::height != 1)
        {
            index -= num_x;
        }
    }
    
    // and store the data in GlobalVars::processTasks
    GlobalVars::processTasks = buffer_lst;

    file.close();
}

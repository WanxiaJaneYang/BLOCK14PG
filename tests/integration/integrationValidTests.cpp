#include "Chunk.h"
#include "IntegrationTestHelper.h"

TEST(Singletest, HandlesValidIntegration)
{
    // Chunk matrix(188, 250, 8, '?');//the FAST

    Chunk matrix(700, 500, 120, '?');//the combination
    // Chunk matrix(255, 255, 255, '?');//the 

    // Redirect std::cout to oss
    std::ostringstream oss;
    StreamRedirector redirect(std::cout, oss.rdbuf());

    // function being tested
    startThreads();

    std::string line;
    std::istringstream iss(oss.str());
    std::string outputPath = "../../tests/integration/valid_test_cases/_outcome.txt";
    std::ofstream outFile(outputPath);

    if (!outFile.is_open())
    {
        std::cerr << "Failed to open the output file!" << std::endl;
        return; // Exit the function or handle the error as appropriate
    }

    if (oss.str().empty())
    {
        std::cerr << "No data to write!" << std::endl;
    }

    int x, y, z, length, width, height;
    char comma;
    std::string label;

    while (std::getline(iss, line))
    {
        // std::cerr << "getting line: " << line << std::endl;
        std::istringstream lineStream(line);
        // Collect size parameters
        lineStream >> x >> comma >> y >> comma >> z >> comma >> length >> comma >> width >> comma >> height >> comma;
                std::getline(lineStream, label);

        // std::cerr << "x: " << x << " y: " << y << " z: " << z << " length: " << length << " width: " << width << " height: " << height << " label: " << label << std::endl;
        matrix.changeRectangle(x, y, z, length, width, height, label);
    }

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.matrix[i].size(); j++)
        {
            for (int k = 0; k < matrix.matrix[i][j].size(); k++)
            {
                outFile << matrix.matrix[i][j][k];
                if (k == matrix.matrix[i][j].size() - 1)
                {
                    outFile << std::endl;
                }
            }
        }
        outFile << std::endl;
    }

    outFile.close(); // Close the file before checking its size
    ASSERT_FALSE(std::__fs::filesystem::file_size(outputPath) == 0) << "Output file is empty!";
}

// ASSERT_FALSE(1 == 0) << "Output file is empty!";

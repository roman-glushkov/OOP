#include <iostream>
#include <fstream>

const int REQUIRED_ARGS_COUNT = 3;

const std::string ERROR_INVALID_ARGS = "Invalid arguments count\n";
const std::string ERROR_READ_OPEN = "Failed to open ";
const std::string ERROR_READ_OPEN_END = " for reading\n";
const std::string ERROR_WRITE_OPEN = "Failed to open ";
const std::string ERROR_WRITE_OPEN_END = " for writing\n";
const std::string ERROR_WRITE_FAILED = "Failed to save data on disk\n";
const std::string ERROR_READ_FAILED = "Failed to read data from input file\n";
const std::string USAGE_MESSAGE = "Usage: copyfile.exe <input file> <output file>\n";

int main(int argc, char * argv[])
{
    if (argc != REQUIRED_ARGS_COUNT)
    {
        std::cout << ERROR_INVALID_ARGS
             << USAGE_MESSAGE;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open())
    {
        std::cout << ERROR_READ_OPEN << argv[1] << ERROR_READ_OPEN_END;
        return 1;
    }

    std::ofstream output(argv[2]);
    if (!output.is_open())
    {
        std::cout << ERROR_WRITE_OPEN << argv[2] << ERROR_WRITE_OPEN_END;
        return 1;
    }

    char ch;

    while (input.get(ch))
    {
        if (!output.put(ch))
        {
            std::cout << ERROR_WRITE_FAILED;
            return 1;
        }
    }
    if (!input.eof())
    {
        std::cout << ERROR_READ_FAILED;
        return 1;
    }
    if (!output.flush())
    {
        std::cout << ERROR_WRITE_FAILED;
        return 1;
    }

    return 0;
}
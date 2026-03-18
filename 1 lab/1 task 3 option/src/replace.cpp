#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>

const char* HELP_TEXT =
    "Program to replace substrings in text.\n"
    "Usage:\n"
    "  replace.exe <input_file> <output_file> <search_string> <replace_string>\n"
    "  or run without arguments to input via stdin:\n"
    "    first line: search string\n"
    "    second line: replace string\n"
    "    then text to replace (until end of input)\n"
    "  replace.exe -h - show this help\n";

const std::string ERROR_MSG = "ERROR";
const char* HELP_FLAG = "-h";

const int ARGS_HELP = 2;     
const int ARGS_STDIN = 1;     
const int ARGS_FULL = 5;      

const int IDX_INPUT_FILE = 1;
const int IDX_OUTPUT_FILE = 2;
const int IDX_SEARCH_STR = 3;
const int IDX_REPLACE_STR = 4;

const char CARRIAGE_RETURN_CHAR = '\r';
const char LINE_FEED_CHAR = '\n';


std::string replaceAll(std::string str, const std::string& from, const std::string& to)
{
    if (from.empty()) return str;

    size_t startPos = 0;
    while ((startPos = str.find(from, startPos)) != std::string::npos)
    {
        str.replace(startPos, from.length(), to);
        startPos += to.length();
    }
    return str;
}

void removeTrailingCarriageReturn(std::string& str)
{
    if (!str.empty() && str.back() == CARRIAGE_RETURN_CHAR)
    {
        str.pop_back();
    }
}

void printHelp()
{
    std::cout << HELP_TEXT;
}

int main(int argc, char* argv[])
{
    if (argc == ARGS_HELP && std::strcmp(argv[1], HELP_FLAG) == 0)
    {
        printHelp();
        return 0;
    }

    if (argc == ARGS_STDIN)
    {
        std::string search, replace;
        if (!std::getline(std::cin, search))
        {
            std::cout << ERROR_MSG << std::endl;
            return 1;
        }
        removeTrailingCarriageReturn(search);

        if (!std::getline(std::cin, replace))
        {
            std::cout << ERROR_MSG << std::endl;
            return 1;
        }
        removeTrailingCarriageReturn(replace);

        std::string line;
        while (std::getline(std::cin, line))
        {
            removeTrailingCarriageReturn(line);
            std::cout << replaceAll(line, search, replace) << std::endl;
        }
        return 0;
    }

    if (argc == ARGS_FULL)
    {
        std::string inputFile = argv[IDX_INPUT_FILE];
        std::string outputFile = argv[IDX_OUTPUT_FILE];
        std::string search = argv[IDX_SEARCH_STR];
        std::string replace = argv[IDX_REPLACE_STR];

        if (inputFile == outputFile)
        {
            std::cout << ERROR_MSG << std::endl;
            return 1;
        }

        std::ifstream inFile(inputFile, std::ios::binary);
        if (!inFile.is_open())
        {
            std::cout << ERROR_MSG << std::endl;
            return 1;
        }

        std::ofstream outFile(outputFile, std::ios::binary);
        if (!outFile.is_open())
        {
            std::cout << ERROR_MSG << std::endl;
            return 1;
        }

        std::string line;
        while (std::getline(inFile, line))
        {
            outFile << replaceAll(line, search, replace) << LINE_FEED_CHAR;
        }
        return 0;
    }

    std::cout << ERROR_MSG << std::endl;
    return 1;
}
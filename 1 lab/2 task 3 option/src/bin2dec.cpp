#include <iostream>
#include <string>
#include <cstdint>

const std::string USAGE_MESSAGE = "Usage:\n  bin2dec.exe <binary_number>\n  bin2dec.exe -h\n";
const std::string ERROR_OUTPUT = "ERROR";
const std::string ERROR_EMPTY_INPUT = "input is empty\n";
const std::string ERROR_LENGTH_EXCEEDED = "length > 32 bits\n";
const std::string ERROR_INVALID_CHAR = "invalid character detected: ";
const std::string ERROR_WRONG_ARGS = "wrong number of arguments\n";

const size_t MAX_BINARY_LENGTH = 32;
const int EXPECTED_ARGS = 2;

bool ConvertBinaryToDecimal(const std::string& binary, uint32_t& result)
{
    if (binary.empty())
    {
        std::cout << ERROR_EMPTY_INPUT;
        return false;
    }

    result = 0;

    if (binary.length() > MAX_BINARY_LENGTH)
    {
        std::cout << ERROR_LENGTH_EXCEEDED;
        return false;
    }

    for (char ch : binary)
    {
        if (ch != '0' && ch != '1')
        {
            std::cout << ERROR_INVALID_CHAR << ch << "\n";
            return false;
        }

        result <<= 1;

        if (ch == '1')
        {
            result |= 1;
        }
    }

    return true;
}

int main(int argc, char* argv[])
{
    if (argc != EXPECTED_ARGS)
    {
        std::cout << ERROR_WRONG_ARGS;
        std::cout << ERROR_OUTPUT;
        return 1;
    }

    if (std::string(argv[1]) == "-h")
    {
        std::cout << USAGE_MESSAGE;
        return 0;
    }

    std::string input = argv[1];
    uint32_t result = 0;

    if (!ConvertBinaryToDecimal(input, result))
    {
        std::cout << ERROR_OUTPUT;
        return 1;
    }

    std::cout << result << std::endl;

    return 0;
}
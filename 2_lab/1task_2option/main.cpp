#include <iostream>
#include "functions.h"

const std::string ERROR_INVALID_DATA = "ERROR";

int main()
{
    bool isValid = true;

    auto numbers = ReadNumbers(std::cin, isValid);

    if (!isValid)
    {
        std::cout << ERROR_INVALID_DATA << std::endl;
        return 0;
    }

    auto processed = ProcessNumbers(numbers);

    PrintSortedNumbers(processed, std::cout);

    return 0;
}
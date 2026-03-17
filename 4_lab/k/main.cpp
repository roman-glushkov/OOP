#include <iostream>
#include "functions.h"

int main()
{
    bool isValid = true;
    auto lines = ReadLines(std::cin, isValid);

    if (!isValid)
    {
        return 0;
    }

    for (const auto& line : lines)
    {
        std::cout << HtmlDecode(line) << std::endl;
    }

    return 0;
}
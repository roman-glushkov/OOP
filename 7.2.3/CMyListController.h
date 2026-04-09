#pragma once

#include <iostream>

class CMyListController
{
public:
    static void ProcessCommands(std::istream& input = std::cin, std::ostream& output = std::cout);
};
#pragma once
#include <iostream>
#include "CDate.h"

class CDateController
{
public:
    static void ProcessCommands(std::istream& input = std::cin, std::ostream& output = std::cout);
};
#include "ShapeController.h"
#include <iostream>

int main()
{
    ShapeController controller(std::cin, std::cout);
    controller.ProcessCommands();
    return 0;
}
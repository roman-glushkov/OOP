#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"
#include "CDate.h"
#include "CDateController.h"
#include <sstream>

TEST_CASE("Controller: print")
{
    std::istringstream input("24.12.2020");
    std::ostringstream output;
    CDateController::ProcessCommands(input, output);
    CHECK(output.str() == "24.12.2020 (Day:24, Month:12, Year:2020, WeekDay:4)\n");
}
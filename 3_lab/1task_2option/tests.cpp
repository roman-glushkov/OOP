#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "Car.h"
#include <sstream>

void ProcessCommands(std::istream& input, std::ostream& output);

TEST_CASE("Test 1 Default state")
{
    std::istringstream input("Info\n");
    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Engine: off\n"
        "Direction: standing still\n"
        "Speed: 0\n"
        "Gear: 0\n");
}

TEST_CASE("Test 2 EngineOn")
{
    std::istringstream input(
        "EngineOn\n"
        "Info\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Engine: on\n"
        "Direction: standing still\n"
        "Speed: 0\n"
        "Gear: 0\n");
}

TEST_CASE("Test 3 EngineOff while moving")
{
    std::istringstream input(
        "EngineOn\n"
        "SetGear 1\n"
        "SetSpeed 10\n"
        "EngineOff\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Car must be stopped and in neutral gear\n");
}

TEST_CASE("Test 4 EngineOff on gear")
{
    std::istringstream input(
        "EngineOn\n"
        "SetGear 1\n"
        "EngineOff\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Car must be stopped and in neutral gear\n");
}

TEST_CASE("Test 5 Correct acceleration")
{
    std::istringstream input(
        "EngineOn\n"
        "SetGear 1\n"
        "SetSpeed 25\n"
        "Info\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Engine: on\n"
        "Direction: forward\n"
        "Speed: 25\n"
        "Gear: 1\n");
}

TEST_CASE("Test 6 Speed out of gear range")
{
    std::istringstream input(
        "EngineOn\n"
        "SetGear 1\n"
        "SetSpeed 40\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Speed is out of gear range\n");
}

TEST_CASE("Test 7 Unsuitable gear change")
{
    std::istringstream input(
        "EngineOn\n"
        "SetGear 1\n"
        "SetSpeed 15\n"
        "SetGear 3\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Unsuitable current speed\n");
}

TEST_CASE("Test 8 Cannot accelerate on neutral")
{
    std::istringstream input(
        "EngineOn\n"
        "SetGear 1\n"
        "SetSpeed 20\n"
        "SetGear 0\n"
        "SetSpeed 30\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Cannot accelerate on neutral\n");
}

TEST_CASE("Test 9 Neutral deceleration allowed")
{
    std::istringstream input(
        "EngineOn\n"
        "SetGear 1\n"
        "SetSpeed 25\n"
        "SetGear 0\n"
        "SetSpeed 10\n"
        "Info\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Engine: on\n"
        "Direction: forward\n"
        "Speed: 10\n"
        "Gear: 0\n");
}

TEST_CASE("Test 10 Reverse driving")
{
    std::istringstream input(
        "EngineOn\n"
        "SetGear -1\n"
        "SetSpeed 15\n"
        "Info\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Engine: on\n"
        "Direction: backward\n"
        "Speed: 15\n"
        "Gear: -1\n");
}

TEST_CASE("Test 11 Cannot reverse while moving")
{
    std::istringstream input(
        "EngineOn\n"
        "SetGear 1\n"
        "SetSpeed 10\n"
        "SetGear -1\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Cannot reverse while moving\n");
}

TEST_CASE("Test 12 Cannot switch direction without stop")
{
    std::istringstream input(
        "EngineOn\n"
        "SetGear -1\n"
        "SetSpeed 10\n"
        "SetGear 0\n"
        "SetGear 1\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Unsuitable current speed\n");
}

TEST_CASE("Test 13 Stop and change direction")
{
    std::istringstream input(
        "EngineOn\n"
        "SetGear -1\n"
        "SetSpeed 10\n"
        "SetGear 0\n"
        "SetSpeed 0\n"
        "SetGear 1\n"
        "SetSpeed 10\n"
        "Info\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Engine: on\n"
        "Direction: forward\n"
        "Speed: 10\n"
        "Gear: 1\n");
}

TEST_CASE("Test 14 Negative speed")
{
    std::istringstream input(
        "EngineOn\n"
        "SetGear 1\n"
        "SetSpeed -5\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Speed cannot be negative\n");
}

TEST_CASE("Test 15 Speed while engine off")
{
    std::istringstream input(
        "SetSpeed 10\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Cannot set speed while engine is off\n");
}

TEST_CASE("Test 16 Gear while engine off")
{
    std::istringstream input(
        "SetGear 1\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Cannot set gear while engine is off\n");
}

TEST_CASE("Test 17 Invalid gear")
{
    std::istringstream input(
        "EngineOn\n"
        "SetGear 8\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Invalid gear\n");
}

TEST_CASE("Test 18 Invalid gear argument")
{
    std::istringstream input(
        "SetGear abc\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Invalid command argument\n");
}

TEST_CASE("Test 19 Invalid speed argument")
{
    std::istringstream input(
        "SetSpeed hello\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Invalid command argument\n");
}

TEST_CASE("Test 20 Unknown command")
{
    std::istringstream input(
        "Fly\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Unknown command\n");
}

TEST_CASE("Test 21 Integration test")
{
    std::istringstream input(
        "Info\n"
        "EngineOn\n"
        "SetGear 1\n"
        "SetSpeed 30\n"
        "SetGear 2\n"
        "SetSpeed 40\n"
        "SetGear 3\n"
        "SetSpeed 55\n"
        "SetGear 0\n"
        "SetSpeed 20\n"
        "SetSpeed 10\n"
        "SetGear 1\n"
        "SetSpeed 20\n"
        "Info\n");

    std::ostringstream output;

    ProcessCommands(input, output);

    CHECK(output.str() ==
        "Engine: off\n"
        "Direction: standing still\n"
        "Speed: 0\n"
        "Gear: 0\n"
        "Engine: on\n"
        "Direction: forward\n"
        "Speed: 20\n"
        "Gear: 1\n");
}
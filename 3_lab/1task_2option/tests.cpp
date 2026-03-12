#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "TestController.h"

TEST_CASE("Test 1 Default state")
{
    TestController test;
    
    test.Info();

    CHECK(test.GetOutput() ==
        "Engine: off\n"
        "Direction: standing still\n"
        "Speed: 0\n"
        "Gear: 0\n");
}

TEST_CASE("Test 2 EngineOn")
{
    TestController test;
    
    test.EngineOn();
    test.Info();

    CHECK(test.GetOutput() ==
        "Engine: on\n"
        "Direction: standing still\n"
        "Speed: 0\n"
        "Gear: 0\n");
}

TEST_CASE("Test 3 EngineOff while moving")
{
    TestController test;
    
    test.EngineOn();
    test.SetGear(1);
    test.SetSpeed(10);
    test.EngineOff();

    CHECK(test.GetOutput() == "Car must be stopped and in neutral gear\n");
}

TEST_CASE("Test 4 EngineOff on gear")
{
    TestController test;
    
    test.EngineOn();
    test.SetGear(1);
    test.EngineOff();

    CHECK(test.GetOutput() == "Car must be stopped and in neutral gear\n");
}

TEST_CASE("Test 5 Correct acceleration")
{
    TestController test;
    
    test.EngineOn();
    test.SetGear(1);
    test.SetSpeed(25);
    test.Info();

    CHECK(test.GetOutput() ==
        "Engine: on\n"
        "Direction: forward\n"
        "Speed: 25\n"
        "Gear: 1\n");
}

TEST_CASE("Test 6 Speed out of gear range")
{
    TestController test;
    
    test.EngineOn();
    test.SetGear(1);
    test.SetSpeed(40);

    CHECK(test.GetOutput() == "Speed is out of gear range\n");
}

TEST_CASE("Test 7 Unsuitable gear change")
{
    TestController test;
    
    test.EngineOn();
    test.SetGear(1);
    test.SetSpeed(15);
    test.SetGear(3);

    CHECK(test.GetOutput() == "Unsuitable current speed\n");
}

TEST_CASE("Test 8 Cannot accelerate on neutral")
{
    TestController test;
    
    test.EngineOn();
    test.SetGear(1);
    test.SetSpeed(20);
    test.SetGear(0);
    test.SetSpeed(30);

    CHECK(test.GetOutput() == "Cannot accelerate on neutral\n");
}

TEST_CASE("Test 9 Neutral deceleration allowed")
{
    TestController test;
    
    test.EngineOn();
    test.SetGear(1);
    test.SetSpeed(25);
    test.SetGear(0);
    test.SetSpeed(10);
    test.Info();

    CHECK(test.GetOutput() ==
        "Engine: on\n"
        "Direction: forward\n"
        "Speed: 10\n"
        "Gear: 0\n");
}

TEST_CASE("Test 10 Reverse driving")
{
    TestController test;
    
    test.EngineOn();
    test.SetGear(-1);
    test.SetSpeed(15);
    test.Info();

    CHECK(test.GetOutput() ==
        "Engine: on\n"
        "Direction: backward\n"
        "Speed: 15\n"
        "Gear: -1\n");
}

TEST_CASE("Test 11 Cannot reverse while moving")
{
    TestController test;
    
    test.EngineOn();
    test.SetGear(1);
    test.SetSpeed(10);
    test.SetGear(-1);

    CHECK(test.GetOutput() == "Cannot reverse while moving\n");
}

TEST_CASE("Test 12 Cannot switch direction without stop")
{
    TestController test;
    
    test.EngineOn();
    test.SetGear(-1);
    test.SetSpeed(10);
    test.SetGear(0);
    test.SetGear(1);

    CHECK(test.GetOutput() == "Unsuitable current speed\n");
}

TEST_CASE("Test 13 Stop and change direction")
{
    TestController test;
    
    test.EngineOn();
    test.SetGear(-1);
    test.SetSpeed(10);
    test.SetGear(0);
    test.SetSpeed(0);
    test.SetGear(1);
    test.SetSpeed(10);
    test.Info();

    CHECK(test.GetOutput() ==
        "Engine: on\n"
        "Direction: forward\n"
        "Speed: 10\n"
        "Gear: 1\n");
}

TEST_CASE("Test 14 Negative speed")
{
    TestController test;
    
    test.EngineOn();
    test.SetGear(1);
    test.SetSpeed(-5);

    CHECK(test.GetOutput() == "Speed cannot be negative\n");
}

TEST_CASE("Test 15 Speed while engine off")
{
    TestController test;
    
    test.SetSpeed(10);

    CHECK(test.GetOutput() == "Cannot set speed while engine is off\n");
}

TEST_CASE("Test 16 Gear while engine off")
{
    TestController test;
    
    test.SetGear(1);

    CHECK(test.GetOutput() == "Cannot set gear while engine is off\n");
}

TEST_CASE("Test 17 Invalid gear")
{
    TestController test;
    
    test.EngineOn();
    test.SetGear(8);

    CHECK(test.GetOutput() == "Invalid gear\n");
}

TEST_CASE("Test 18 Integration test")
{
    TestController test;
    
    test.Info();
    test.EngineOn();
    test.SetGear(1);
    test.SetSpeed(30);
    test.SetGear(2);
    test.SetSpeed(40);
    test.SetGear(3);
    test.SetSpeed(55);
    test.SetGear(0);
    test.SetSpeed(20);
    test.SetSpeed(10);
    test.SetGear(1);
    test.SetSpeed(20);
    test.Info();

    CHECK(test.GetOutput() ==
        "Engine: off\n"
        "Direction: standing still\n"
        "Speed: 0\n"
        "Gear: 0\n"
        "Engine: on\n"
        "Direction: forward\n"
        "Speed: 20\n"
        "Gear: 1\n");
}
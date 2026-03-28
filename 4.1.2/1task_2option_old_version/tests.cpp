#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "ShapeController.h"
#include "Shape.h"
#include <sstream>
#include <memory>

TEST_CASE("isValidColor - valid 6-digit hex colors") 
{
    CHECK(isValidColor("ff0000") == true); 
    CHECK(isValidColor("00ff00") == true);  
    CHECK(isValidColor("0000ff") == true);  
    CHECK(isValidColor("123abc") == true);  
    CHECK(isValidColor("ABCDEF") == true); 
    CHECK(isValidColor("a1b2c3") == true);  
}

TEST_CASE("isValidColor - invalid colors") 
{
    CHECK(isValidColor("ff000") == false);  
    CHECK(isValidColor("ff00000") == false);
    CHECK(isValidColor("ff000g") == false);  
    CHECK(isValidColor("") == false);      
    CHECK(isValidColor("12345") == false); 
    CHECK(isValidColor("1234567") == false);
    CHECK(isValidColor("!@#$%^") == false); 
}

TEST_CASE("ERROR_EMPTY_INPUT - empty string")
{
    std::stringstream buffer;
    auto old_cout = std::cout.rdbuf(buffer.rdbuf());
    
    auto shape = parseShape("");
    
    std::cout.rdbuf(old_cout);
    
    REQUIRE(shape == nullptr);
    CHECK(buffer.str() == "ERROR: empty input\n");
}

TEST_CASE("ERROR_UNKNOWN_TYPE - invalid shape type")
{
    std::stringstream buffer;
    auto old_cout = std::cout.rdbuf(buffer.rdbuf());
    
    auto shape = parseShape("hexagon 0 0 1 1 2 2 3 3 4 4 FF0000 00FF00");
    
    std::cout.rdbuf(old_cout);
    
    REQUIRE(shape == nullptr);
    CHECK(buffer.str() == "ERROR: unknown shape type\n");
}

TEST_CASE("ERROR_INVALID_FORMAT - rectangle missing coordinates")
{
    std::stringstream buffer;
    auto old_cout = std::cout.rdbuf(buffer.rdbuf());
    
    auto shape = parseShape("rectangle 0 0 10 0 10 10");
    
    std::cout.rdbuf(old_cout);
    
    REQUIRE(shape == nullptr);
    CHECK(buffer.str() == "ERROR: invalid input format\n");
}

TEST_CASE("ERROR_INVALID_FORMAT - circle missing radius")
{
    std::stringstream buffer;
    auto old_cout = std::cout.rdbuf(buffer.rdbuf());
    
    auto shape = parseShape("circle 0 0 FF0000 00FF00");
    
    std::cout.rdbuf(old_cout);
    
    REQUIRE(shape == nullptr);
    CHECK(buffer.str() == "ERROR: invalid input format\n");
}

TEST_CASE("ERROR_INVALID_FORMAT - line missing point")
{
    std::stringstream buffer;
    auto old_cout = std::cout.rdbuf(buffer.rdbuf());
    
    auto shape = parseShape("line 0 0 FF0000");
    
    std::cout.rdbuf(old_cout);
    
    REQUIRE(shape == nullptr);
    CHECK(buffer.str() == "ERROR: invalid input format\n");
}

TEST_CASE("ERROR_INVALID_COLOR - outline invalid (too short)")
{
    std::stringstream buffer;
    auto old_cout = std::cout.rdbuf(buffer.rdbuf());
    
    auto shape = parseShape("square 0 0 5 0 5 5 0 5 FF000 00FF00");
    
    std::cout.rdbuf(old_cout);
    
    REQUIRE(shape == nullptr);
    CHECK(buffer.str() == "ERROR: invalid color\n");
}

TEST_CASE("ERROR_INVALID_COLOR - line color invalid")
{
    std::stringstream buffer;
    auto old_cout = std::cout.rdbuf(buffer.rdbuf());
    
    auto shape = parseShape("line 0 0 10 10 FFF00G");
    
    std::cout.rdbuf(old_cout);
    
    REQUIRE(shape == nullptr);
    CHECK(buffer.str() == "ERROR: invalid color\n");
}

TEST_CASE("ERROR_EXTRA_DATA - extra numbers at end")
{
    std::stringstream buffer;
    auto old_cout = std::cout.rdbuf(buffer.rdbuf());
    
    auto shape = parseShape("rectangle 0 0 10 0 10 10 0 10 FF0000 00FF00 123");
    
    std::cout.rdbuf(old_cout);
    
    REQUIRE(shape == nullptr);
    CHECK(buffer.str() == "ERROR: extra data in input\n");
}

TEST_CASE("ERROR_INVALID_RADIUS - radius is negative")
{
    std::stringstream buffer;
    auto old_cout = std::cout.rdbuf(buffer.rdbuf());
    
    auto shape = parseShape("circle 0 0 -5 FF0000 00FF00");
    
    std::cout.rdbuf(old_cout);
    
    REQUIRE(shape == nullptr);
    CHECK(buffer.str() == "ERROR: radius must be positive\n");
}

TEST_CASE("Valid shapes parse correctly")
{
    SECTION("Rectangle")
    {
        auto shape = parseShape("rectangle 0 0 10 0 10 10 0 10 FF0000 00FF00");
        REQUIRE(shape != nullptr);
        CHECK(shape->ToString() == "Rectangle [(0, 0), (10, 0), (10, 10), (0, 10)]");
    }
    
    SECTION("Square")
    {
        auto shape = parseShape("square 0 0 5 0 5 5 0 5 0000FF FFFF00");
        REQUIRE(shape != nullptr);
        CHECK(shape->ToString() == "Square [(0, 0), (5, 0), (5, 5), (0, 5)]");
    }
    
    SECTION("Circle")
    {
        auto shape = parseShape("circle 0 0 10 FF0000 00FF00");
        REQUIRE(shape != nullptr);
        CHECK(shape->ToString() == "Circle [center: (0, 0), radius: 10]");
    }
    
    SECTION("Triangle")
    {
        auto shape = parseShape("triangle 0 0 10 0 5 8.66 FF0000 00FF00");
        REQUIRE(shape != nullptr);
        CHECK(shape->ToString() == "Triangle [(0, 0), (10, 0), (5, 8.66)]");
    }
    
    SECTION("Line")
    {
        auto shape = parseShape("line 0 0 10 10 FF0000");
        REQUIRE(shape != nullptr);
        CHECK(shape->ToString() == "Line [(0, 0) -> (10, 10)]");
    }
    
    SECTION("Case insensitive type")
    {
        auto shape = parseShape("CIRCLE 0 0 10 FF0000 00FF00");
        REQUIRE(shape != nullptr);
        CHECK(shape->ToString() == "Circle [center: (0, 0), radius: 10]");
    }
}

TEST_CASE("Basic area calculations")
{
    SECTION("Rectangle area")
    {
        auto shape = parseShape("rectangle 0 0 10 0 10 5 0 5 FF0000 00FF00");
        REQUIRE(shape != nullptr);
        CHECK(shape->Area() == 50.0);
    }
    
    SECTION("Circle area")
    {
        auto shape = parseShape("circle 0 0 10 FF0000 00FF00");
        REQUIRE(shape != nullptr);
        CHECK(shape->Area() == Approx(314.159).epsilon(0.001));
    }
    
    SECTION("Line area is zero")
    {
        auto shape = parseShape("line 0 0 10 10 FF0000");
        REQUIRE(shape != nullptr);
        CHECK(shape->Area() == 0.0);
    }
}

TEST_CASE("Basic perimeter calculations")
{
    SECTION("Rectangle perimeter")
    {
        auto shape = parseShape("rectangle 0 0 10 0 10 5 0 5 FF0000 00FF00");
        REQUIRE(shape != nullptr);
        CHECK(shape->Perimeter() == 30.0);
    }
    
    SECTION("Line perimeter is length")
    {
        auto shape = parseShape("line 0 0 3 4 FF0000");
        REQUIRE(shape != nullptr);
        CHECK(shape->Perimeter() == 5.0);
    }
}
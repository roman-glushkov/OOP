#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "ShapeController.h"
#include "Shape.h"
#include <sstream>
#include <memory>

// ========== ТЕСТЫ ДЛЯ isValidColor ==========
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

// ========== ТЕСТЫ ДЛЯ parseShape ==========
TEST_CASE("parseShape - valid rectangle")
{
    std::string input = "rectangle 0 0 10 0 10 5 0 5 ff0000 00ff00";
    auto shape = parseShape(input);
    
    REQUIRE(shape != nullptr);
    CHECK(shape->ToString() == "Rectangle [(0, 0), (10, 0), (10, 5), (0, 5)]");
    CHECK(shape->outlineColor == "ff0000");
    CHECK(shape->fillColor == "00ff00");
}

TEST_CASE("parseShape - valid square")
{
    std::string input = "square 0 0 5 0 5 5 0 5 0000ff ffff00";
    auto shape = parseShape(input);
    
    REQUIRE(shape != nullptr);
    CHECK(shape->ToString() == "Square [(0, 0), (5, 0), (5, 5), (0, 5)]");
}

TEST_CASE("parseShape - valid circle")
{
    std::string input = "circle 0 0 10 00ff00 ff0000";
    auto shape = parseShape(input);
    
    REQUIRE(shape != nullptr);
    CHECK(shape->ToString() == "Circle [center: (0, 0), radius: 10]");
}

TEST_CASE("parseShape - valid triangle")
{
    std::string input = "triangle 0 0 10 0 5 8.66 800080 ffa500";
    auto shape = parseShape(input);
    
    REQUIRE(shape != nullptr);
    CHECK(shape->ToString() == "Triangle [(0, 0), (10, 0), (5, 8.66)]");
}

TEST_CASE("parseShape - valid rhombus")
{
    std::string input = "rhombus 0 1 1 0 2 1 1 2 00ff00 ff0000";
    auto shape = parseShape(input);
    
    REQUIRE(shape != nullptr);
    CHECK(shape->ToString() == "Rhombus [(0, 1), (1, 0), (2, 1), (1, 2)]");
}

TEST_CASE("parseShape - valid parallelogram")
{
    std::string input = "parallelogram 0 0 5 0 7 3 2 3 ff00ff 00ffff";
    auto shape = parseShape(input);
    
    REQUIRE(shape != nullptr);
    CHECK(shape->ToString() == "Parallelogram [(0, 0), (5, 0), (7, 3), (2, 3)]");
}

TEST_CASE("parseShape - valid trapezoid")
{
    std::string input = "trapezoid 0 0 5 0 4 3 1 3 000000 ffffff";
    auto shape = parseShape(input);
    
    REQUIRE(shape != nullptr);
    CHECK(shape->ToString() == "Trapezoid [(0, 0), (5, 0), (4, 3), (1, 3)]");
}

TEST_CASE("parseShape - valid line")
{
    std::string input = "line 0 0 10 10 ff0000";
    auto shape = parseShape(input);
    
    REQUIRE(shape != nullptr);
    CHECK(shape->ToString() == "Line [(0, 0) -> (10, 10)]");
    CHECK(shape->outlineColor == "ff0000");
    CHECK(shape->fillColor == "none");
}

// ========== ТЕСТЫ НА ОШИБКИ ==========
TEST_CASE("parseShape - ERROR_EMPTY_INPUT")
{
    std::stringstream buffer;
    auto old_cout = std::cout.rdbuf(buffer.rdbuf());
    
    std::string input = "";
    auto shape = parseShape(input);
    
    std::cout.rdbuf(old_cout);
    
    REQUIRE(shape == nullptr);
    CHECK(buffer.str() == "ERROR: empty input\n");
}

TEST_CASE("parseShape - ERROR_INVALID_FORMAT (missing coordinates)")
{
    std::stringstream buffer;
    auto old_cout = std::cout.rdbuf(buffer.rdbuf());
    
    std::string input = "rectangle 0 0 10 0";
    auto shape = parseShape(input);
    
    std::cout.rdbuf(old_cout);
    
    REQUIRE(shape == nullptr);
    CHECK(buffer.str() == "ERROR: invalid input format\n");
}

TEST_CASE("parseShape - ERROR_INVALID_COLOR")
{
    std::stringstream buffer;
    auto old_cout = std::cout.rdbuf(buffer.rdbuf());
    
    std::string input = "circle 0 0 10 ff000 zzzzzz";
    auto shape = parseShape(input);
    
    std::cout.rdbuf(old_cout);
    
    REQUIRE(shape == nullptr);
    CHECK(buffer.str() == "ERROR: invalid color\n");
}

TEST_CASE("parseShape - ERROR_EXTRA_DATA")
{
    std::stringstream buffer;
    auto old_cout = std::cout.rdbuf(buffer.rdbuf());
    
    std::string input = "square 0 0 5 0 5 5 0 5 0000ff ffff00 extra data";
    auto shape = parseShape(input);
    
    std::cout.rdbuf(old_cout);
    
    REQUIRE(shape == nullptr);
    CHECK(buffer.str() == "ERROR: extra data in input\n");
}

TEST_CASE("parseShape - ERROR_INVALID_RADIUS")
{
    std::stringstream buffer;
    auto old_cout = std::cout.rdbuf(buffer.rdbuf());
    
    std::string input = "circle 0 0 -5 00ff00 ff0000";
    auto shape = parseShape(input);
    
    std::cout.rdbuf(old_cout);
    
    REQUIRE(shape == nullptr);
    CHECK(buffer.str() == "ERROR: radius must be positive\n");
}

TEST_CASE("parseShape - ERROR_UNKNOWN_TYPE")
{
    std::stringstream buffer;
    auto old_cout = std::cout.rdbuf(buffer.rdbuf());
    
    std::string input = "hexagon 0 0 10 0 10 5 0 5 ff0000 00ff00";
    auto shape = parseShape(input);
    
    std::cout.rdbuf(old_cout);
    
    REQUIRE(shape == nullptr);
    CHECK(buffer.str() == "ERROR: unknown shape type\n");
}

// ========== ТЕСТЫ ДЛЯ Area() ==========
TEST_CASE("Quadrilateral::Area - rectangle area")
{
    std::string input = "rectangle 0 0 10 0 10 5 0 5 ff0000 00ff00";
    auto shape = parseShape(input);
    
    REQUIRE(shape != nullptr);
    CHECK(shape->Area() == Approx(50.0));
}

TEST_CASE("Circle::Area - circle area")
{
    std::string input = "circle 0 0 10 00ff00 ff0000";
    auto shape = parseShape(input);
    
    REQUIRE(shape != nullptr);
    CHECK(shape->Area() == Approx(314.159265).epsilon(0.001));
}

TEST_CASE("Triangle::Area - triangle area")
{
    std::string input = "triangle 0 0 10 0 5 8.66 800080 ffa500";
    auto shape = parseShape(input);
    
    REQUIRE(shape != nullptr);
    CHECK(shape->Area() == Approx(43.3).epsilon(0.1)); 
}

TEST_CASE("Line::Area - line area")
{
    std::string input = "line 0 0 10 10 ff0000";
    auto shape = parseShape(input);
    
    REQUIRE(shape != nullptr);
    CHECK(shape->Area() == Approx(0.0));
}

// ========== ТЕСТЫ ДЛЯ Perimeter() ==========
TEST_CASE("Quadrilateral::Perimeter - rectangle perimeter")
{
    std::string input = "rectangle 0 0 10 0 10 5 0 5 ff0000 00ff00";
    auto shape = parseShape(input);
    
    REQUIRE(shape != nullptr);
    CHECK(shape->Perimeter() == Approx(30.0));
}

TEST_CASE("Circle::Perimeter - circle perimeter")
{
    std::string input = "circle 0 0 10 00ff00 ff0000";
    auto shape = parseShape(input);
    
    REQUIRE(shape != nullptr);
    CHECK(shape->Perimeter() == Approx(62.8319).epsilon(0.001));
}

TEST_CASE("Triangle::Perimeter - triangle perimeter")
{
    std::string input = "triangle 0 0 10 0 5 8.66 800080 ffa500";
    auto shape = parseShape(input);
    
    REQUIRE(shape != nullptr);
    CHECK(shape->Perimeter() == Approx(30.0).epsilon(0.1));
}

TEST_CASE("Line::Perimeter - line perimeter (length)")
{
    std::string input = "line 0 0 3 4 ff0000";
    auto shape = parseShape(input);
    
    REQUIRE(shape != nullptr);
    CHECK(shape->Perimeter() == Approx(5.0)); 
}

// ========== ТЕСТЫ ДЛЯ findMaxArea ==========
TEST_CASE("findMaxArea - find shape with maximum area")
{
    std::vector<std::shared_ptr<Shape>> shapes;
    
    shapes.push_back(parseShape("rectangle 0 0 10 0 10 5 0 5 ff0000 00ff00"));    
    shapes.push_back(parseShape("circle 0 0 10 00ff00 ff0000"));                    
    shapes.push_back(parseShape("square 0 0 5 0 5 5 0 5 0000ff ffff00"));         
    
    auto maxShape = findMaxArea(shapes);
    
    REQUIRE(maxShape != nullptr);
    CHECK(maxShape->ToString().find("Circle") != std::string::npos);
    CHECK(maxShape->Area() == Approx(314.159).epsilon(0.001));
}

TEST_CASE("findMaxArea - empty vector returns nullptr")
{
    std::vector<std::shared_ptr<Shape>> shapes;
    auto maxShape = findMaxArea(shapes);
    
    CHECK(maxShape == nullptr);
}

// ========== ТЕСТЫ ДЛЯ findMinPerimeter ==========
TEST_CASE("findMinPerimeter - find shape with minimum perimeter")
{
    std::vector<std::shared_ptr<Shape>> shapes;
    
    shapes.push_back(parseShape("rectangle 0 0 10 0 10 5 0 5 ff0000 00ff00"));     
    shapes.push_back(parseShape("circle 0 0 10 00ff00 ff0000"));               
    shapes.push_back(parseShape("square 0 0 1 0 1 1 0 1 0000ff ffff00"));         
    
    auto minShape = findMinPerimeter(shapes);
    
    REQUIRE(minShape != nullptr);
    CHECK(minShape->ToString().find("Square") != std::string::npos);
    CHECK(minShape->Perimeter() == Approx(4.0));
}

TEST_CASE("findMinPerimeter - empty vector returns nullptr")
{
    std::vector<std::shared_ptr<Shape>> shapes;
    auto minShape = findMinPerimeter(shapes);
    
    CHECK(minShape == nullptr);
}

// ========== ТЕСТЫ ДЛЯ printShapeInfo ==========
TEST_CASE("printShapeInfo - prints correct info")
{
    auto shape = parseShape("circle 0 0 10 00ff00 ff0000");
    REQUIRE(shape != nullptr);
    
    std::stringstream buffer;
    auto old_cout = std::cout.rdbuf(buffer.rdbuf());
    
    printShapeInfo(shape, "TEST TITLE");
    
    std::cout.rdbuf(old_cout);
    
    std::string output = buffer.str();
    CHECK(output.find("=== TEST TITLE ===") != std::string::npos);
    CHECK(output.find("Circle [center: (0, 0), radius: 10]") != std::string::npos);
    CHECK(output.find("Area: 314.16") != std::string::npos);
    CHECK(output.find("Perimeter: 62.83") != std::string::npos);
    CHECK(output.find("Outline color: #00ff00") != std::string::npos);
    CHECK(output.find("Fill color: #ff0000") != std::string::npos);
}

TEST_CASE("printShapeInfo - line has no fill color")
{
    auto shape = parseShape("line 0 0 10 10 ff0000");
    REQUIRE(shape != nullptr);
    
    std::stringstream buffer;
    auto old_cout = std::cout.rdbuf(buffer.rdbuf());
    
    printShapeInfo(shape, "LINE TEST");
    
    std::cout.rdbuf(old_cout);
    
    std::string output = buffer.str();
    CHECK(output.find("=== LINE TEST ===") != std::string::npos);
    CHECK(output.find("Line [(0, 0) -> (10, 10)]") != std::string::npos);
    CHECK(output.find("Outline color: #ff0000") != std::string::npos);
    CHECK(output.find("Fill color: #") == std::string::npos); 
}

// ========== ТЕСТЫ ДЛЯ интеграции ==========
TEST_CASE("Full pipeline - process multiple shapes")
{
    std::vector<std::shared_ptr<Shape>> shapes;
    
    auto shape1 = parseShape("rectangle 0 0 10 0 10 5 0 5 ff0000 00ff00");
    auto shape2 = parseShape("circle 0 0 5 0000ff ffff00");                 
    auto shape3 = parseShape("line 1 1 2 2 123456");                         
    
    shapes.push_back(shape1);
    shapes.push_back(shape2);
    shapes.push_back(shape3);
    
    REQUIRE(shapes.size() == 3);
    
    auto maxArea = findMaxArea(shapes);
    auto minPerim = findMinPerimeter(shapes);

    CHECK(maxArea->ToString().find("Circle") != std::string::npos);
    CHECK(minPerim->ToString().find("Line") != std::string::npos);
}
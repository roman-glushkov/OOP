#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "utils/ShapeController.h" 
#include "utils/ShapeParser.h"     
#include "interfaces/IShape.h"
#include "interfaces/ISolidShape.h"
#include "shapes/CLineSegment.h"
#include "shapes/CTriangle.h"
#include "shapes/CRectangle.h"
#include "shapes/CCircle.h"
#include "shapes/CSquare.h"
#include "shapes/CRhombus.h"
#include "shapes/CParallelogram.h"
#include "shapes/CTrapezoid.h"
#include <sstream>
#include <memory>
#include <iomanip>
#include <functional>

std::string CaptureOutput(std::function<void()> func)
{
    std::stringstream buffer; // создание буфера
    auto old_cout = std::cout.rdbuf(buffer.rdbuf()); // перенаправление cout
    func(); // вызов функции
    std::cout.rdbuf(old_cout); // восстановление cout
    return buffer.str(); // возращает захваченный вывод
}

void SimulateInput(const std::string& input, std::function<void()> func)
{
    auto old_cin = std::cin.rdbuf(); // сохраняем старый буфер
    std::istringstream iss(input); // создаем поток из строки
    std::cin.rdbuf(iss.rdbuf()); // перенаправляем cin на нашу строку
    func(); // выполняем функцию
    std::cin.rdbuf(old_cin); // восстанавливаем старый буфер
}

TEST_CASE("Test 1: All error messages")
{
    SECTION("Empty input")
    {
        std::string output = CaptureOutput([]() {
            ShapeParser::ParseShape("");
        });
        REQUIRE(output == Config::ERROR_PREFIX + Config::ERROR_EMPTY_INPUT);
    }
    
    SECTION("Unknown shape type")
    {
        std::string output = CaptureOutput([]() {
            ShapeParser::ParseShape("hexagon 0 0 1 1 FF0000 00FF00");
        });
        REQUIRE(output == Config::ERROR_PREFIX + Config::ERROR_UNKNOWN_TYPE);
    }
    
    SECTION("Invalid color - too short")
    {
        std::string output = CaptureOutput([]() {
            ShapeParser::ParseShape("line 0 0 10 10 FF000");
        });
        REQUIRE(output == Config::ERROR_PREFIX + Config::ERROR_INVALID_COLOR);
    }
    
    SECTION("Invalid color - too long")
    {
        std::string output = CaptureOutput([]() {
            ShapeParser::ParseShape("line 0 0 10 10 FFFFFF0");
        });
        REQUIRE(output == Config::ERROR_PREFIX + Config::ERROR_INVALID_COLOR);
    }
    
    SECTION("Invalid color - non-hex character")
    {
        std::string output = CaptureOutput([]() {
            ShapeParser::ParseShape("line 0 0 10 10 FF00GG");
        });
        REQUIRE(output == Config::ERROR_PREFIX + Config::ERROR_INVALID_COLOR);
    }
    
    SECTION("Invalid radius - negative")
    {
        std::string output = CaptureOutput([]() {
            ShapeParser::ParseShape("circle 0 0 -5 FF0000 00FF00");
        });
        REQUIRE(output == Config::ERROR_PREFIX + Config::ERROR_INVALID_RADIUS);
    }
    
    SECTION("Invalid radius - zero")
    {
        std::string output = CaptureOutput([]() {
            ShapeParser::ParseShape("circle 0 0 0 FF0000 00FF00");
        });
        REQUIRE(output == Config::ERROR_PREFIX + Config::ERROR_INVALID_RADIUS);
    }
    
    SECTION("Extra data at end")
    {
        std::string output = CaptureOutput([]() {
            ShapeParser::ParseShape("line 0 0 10 10 FF0000 extra");
        });
        REQUIRE(output == Config::ERROR_PREFIX + Config::ERROR_EXTRA_DATA);
    }
    
    SECTION("Invalid format - missing coordinates")
    {
        std::string output = CaptureOutput([]() {
            ShapeParser::ParseShape("rectangle 0 0 10 0 10 off10");
        });
        REQUIRE(output == Config::ERROR_PREFIX + Config::ERROR_INVALID_COLOR);
    }
    
    SECTION("Invalid format - missing color")
    {
        std::string output = CaptureOutput([]() {
            ShapeParser::ParseShape("triangle 0 0 10 0 5 5 FF0000");
        });
        REQUIRE(output == Config::ERROR_PREFIX + Config::ERROR_INVALID_FORMAT);
    }
}

TEST_CASE("Test 2: Direct function testing")
{
    SECTION("CLineSegment direct test")
    {
        CLineSegment line(CPoint(1, 2), CPoint(4, 6), 0xFF0000);
        REQUIRE(line.GetStartPoint().x == 1);
        REQUIRE(line.GetStartPoint().y == 2);
        REQUIRE(line.GetEndPoint().x == 4);
        REQUIRE(line.GetEndPoint().y == 6);
        REQUIRE(line.GetArea() == 0.0);
        REQUIRE(line.GetPerimeter() == 5.0);
        REQUIRE(line.GetOutlineColor() == 0xFF0000);
        REQUIRE(line.ToString() == "Line [(1, 2) -> (4, 6)]");
    }
    
    SECTION("CRectangle direct test")
    {
        CRectangle rect(CPoint(1, 1), 5, 3, 0x00FF00, 0x0000FF);
        REQUIRE(rect.GetLeftTop().x == 1);
        REQUIRE(rect.GetLeftTop().y == 1);
        REQUIRE(rect.GetWidth() == 5);
        REQUIRE(rect.GetHeight() == 3);
        REQUIRE(rect.GetRightBottom().x == 6);
        REQUIRE(rect.GetRightBottom().y == 4);
        REQUIRE(rect.GetArea() == 15.0);
        REQUIRE(rect.GetPerimeter() == 16.0);
        REQUIRE(rect.GetOutlineColor() == 0x00FF00);
        REQUIRE(rect.GetFillColor() == 0x0000FF);
    }
    
    SECTION("CCircle direct test")
    {
        CCircle circle(CPoint(0, 0), 5, 0xFF0000, 0x00FF00);
        REQUIRE(circle.GetCenter().x == 0);
        REQUIRE(circle.GetCenter().y == 0);
        REQUIRE(circle.GetRadius() == 5);
        REQUIRE(circle.GetArea() == Approx(78.5398).epsilon(0.001));
        REQUIRE(circle.GetPerimeter() == Approx(31.4159).epsilon(0.001));
    }
    
    SECTION("CTriangle direct test")
    {
        CTriangle triangle(CPoint(0, 0), CPoint(3, 0), CPoint(0, 4), 0xFF0000, 0x00FF00);
        REQUIRE(triangle.GetVertex1().x == 0);
        REQUIRE(triangle.GetVertex1().y == 0);
        REQUIRE(triangle.GetVertex2().x == 3);
        REQUIRE(triangle.GetVertex2().y == 0);
        REQUIRE(triangle.GetVertex3().x == 0);
        REQUIRE(triangle.GetVertex3().y == 4);
        REQUIRE(triangle.GetArea() == 6.0);
        REQUIRE(triangle.GetPerimeter() == 12.0);
    }
    
    SECTION("CSquare direct test")
    {
        CSquare square(CPoint(2, 2), 4, 0xFF0000, 0x00FF00);
        REQUIRE(square.GetLeftTop().x == 2);
        REQUIRE(square.GetLeftTop().y == 2);
        REQUIRE(square.GetSide() == 4);
        REQUIRE(square.GetRightBottom().x == 6);
        REQUIRE(square.GetRightBottom().y == 6);
        REQUIRE(square.GetArea() == 16.0);
        REQUIRE(square.GetPerimeter() == 16.0);
    }
    
    SECTION("CRhombus direct test")
    {
        CRhombus rhombus(CPoint(0, 0), 8, 6, 0xFF0000, 0x00FF00);
        REQUIRE(rhombus.GetCenter().x == 0);
        REQUIRE(rhombus.GetCenter().y == 0);
        REQUIRE(rhombus.GetDiagonal1() == 8);
        REQUIRE(rhombus.GetDiagonal2() == 6);
        REQUIRE(rhombus.GetVertex1().x == 0);
        REQUIRE(rhombus.GetVertex1().y == -4);
        REQUIRE(rhombus.GetVertex2().x == 3);
        REQUIRE(rhombus.GetVertex2().y == 0);
        REQUIRE(rhombus.GetVertex3().x == 0);
        REQUIRE(rhombus.GetVertex3().y == 4);
        REQUIRE(rhombus.GetVertex4().x == -3);
        REQUIRE(rhombus.GetVertex4().y == 0);
        REQUIRE(rhombus.GetArea() == 24.0);
        REQUIRE(rhombus.GetPerimeter() == Approx(20.0).epsilon(0.001));
    }
}

TEST_CASE("Test 3: Each shape type full program test")
{
    SECTION("Line segment test")
    {
        std::string input = "line 1 2 4 6 FF0000\n";
        
        ShapeController controller;
        std::string output;
        
        SimulateInput(input, [&]() {
            output = CaptureOutput([&]() {
                controller.ReadShapes();
                controller.PrintResults();
            });
        });
        
        REQUIRE(output.find("Line [(1, 2) -> (4, 6)]") != std::string::npos);
        REQUIRE(output.find("Perimeter: 5.00") != std::string::npos);
        REQUIRE(output.find("Outline color: #ff0000") != std::string::npos);
    }
    
    SECTION("Rectangle test")
    {
  
        std::string input = "rectangle 1 1 5 3 FF0000 00FF00\n"; 
        
        ShapeController controller;
        std::string output;
        
        SimulateInput(input, [&]() {
            output = CaptureOutput([&]() {
                controller.ReadShapes();
                controller.PrintResults();
            });
        });
        
        REQUIRE(output.find("Rectangle [(1, 1), (6, 1), (6, 4), (1, 4)]") != std::string::npos);
        REQUIRE(output.find("Area: 15.00") != std::string::npos);
        REQUIRE(output.find("Perimeter: 16.00") != std::string::npos);
        REQUIRE(output.find("Outline color: #ff0000") != std::string::npos);
        REQUIRE(output.find("Fill color: #00ff00") != std::string::npos);
    }
    
    SECTION("Circle test")
    {
        std::string input = "circle 0 0 5 FF0000 00FF00\n";
        
        ShapeController controller;
        std::string output;
        
        SimulateInput(input, [&]() {
            output = CaptureOutput([&]() {
                controller.ReadShapes();
                controller.PrintResults();
            });
        });

        REQUIRE(output.find("Circle [center: (0, 0), radius: 5)]") != std::string::npos);
        REQUIRE(output.find("Area: 78.54") != std::string::npos);
        REQUIRE(output.find("Perimeter: 31.42") != std::string::npos);
    }
    
    SECTION("Triangle test")
    {
        std::string input = "triangle 0 0 3 0 0 4 FF0000 00FF00\n";
        
        ShapeController controller;
        std::string output;
        
        SimulateInput(input, [&]() {
            output = CaptureOutput([&]() {
                controller.ReadShapes();
                controller.PrintResults();
            });
        });
        
        REQUIRE(output.find("Triangle [(0, 0), (3, 0), (0, 4)]") != std::string::npos);
        REQUIRE(output.find("Area: 6.00") != std::string::npos);
        REQUIRE(output.find("Perimeter: 12.00") != std::string::npos);
    }
    
    SECTION("Square test")
    {
        std::string input = "square 2 2 4 FF0000 00FF00\n"; 
        
        ShapeController controller;
        std::string output;
        
        SimulateInput(input, [&]() {
            output = CaptureOutput([&]() {
                controller.ReadShapes();
                controller.PrintResults();
            });
        });

        REQUIRE(output.find("Square [(2, 2), (6, 2), (6, 6), (2, 6)]") != std::string::npos);
        REQUIRE(output.find("Area: 16.00") != std::string::npos);
        REQUIRE(output.find("Perimeter: 16.00") != std::string::npos);
    }
    
    SECTION("Rhombus test")
    {
        std::string input = "rhombus 0 0 8 6 FF0000 00FF00\n";
        
        ShapeController controller;
        std::string output;
        
        SimulateInput(input, [&]() {
            output = CaptureOutput([&]() {
                controller.ReadShapes();
                controller.PrintResults();
            });
        });
        
        REQUIRE(output.find("Rhombus [(0, -4), (3, 0), (0, 4), (-3, 0)]") != std::string::npos);
        REQUIRE(output.find("Area: 24.00") != std::string::npos);
        REQUIRE(output.find("Perimeter: 20.00") != std::string::npos);
    }
    
    SECTION("Parallelogram test")
    {
        std::string input = "parallelogram 0 0 5 0 7 3 FF0000 00FF00\n";
        
        ShapeController controller;
        std::string output;
        
        SimulateInput(input, [&]() {
            output = CaptureOutput([&]() {
                controller.ReadShapes();
                controller.PrintResults();
            });
        });
        
        REQUIRE(output.find("Parallelogram [(0, 0), (5, 0), (7, 3), (2, 3)]") != std::string::npos);
        REQUIRE(output.find("Area: 15.00") != std::string::npos);
    }
    
    SECTION("Trapezoid test")
    {
        std::string input = "trapezoid 0 0 4 0 3 2 1 2 FF0000 00FF00\n";
        
        ShapeController controller;
        std::string output;
        
        SimulateInput(input, [&]() {
            output = CaptureOutput([&]() {
                controller.ReadShapes();
                controller.PrintResults();
            });
        });
        
        REQUIRE(output.find("Trapezoid [(0, 0), (4, 0), (3, 2), (1, 2)]") != std::string::npos);
        REQUIRE(output.find("Area: 6.00") != std::string::npos);
    }
}

TEST_CASE("Test 4: Multiple shapes - find max area and min perimeter")
{
    std::string input = 
        "line 0 0 1 1 000000\n"
        "rectangle 0 0 10 5 FF0000 00FF00\n"       
        "circle 0 0 3 00FF00 0000FF\n"
        "square 0 0 4 FF0000 00FF00\n"
        "triangle 0 0 4 0 2 3 FF0000 00FF00\n"
        "line 0 0 0.5 0.5 000000\n"
        "rectangle 0 0 100 1 FF0000 00FF00\n";     
    
    ShapeController controller;
    std::string output;
    
    SimulateInput(input, [&]() {
        output = CaptureOutput([&]() {
            controller.ReadShapes();
            controller.PrintResults();
        });
    });
    
    REQUIRE(output.find("Total shapes: 7") != std::string::npos);
    
    REQUIRE(output.find("=== SHAPE WITH MAXIMUM AREA ===") != std::string::npos);
    REQUIRE(output.find("Rectangle [(0, 0), (100, 0), (100, 1), (0, 1)]") != std::string::npos);
    REQUIRE(output.find("Area: 100.00") != std::string::npos);
    
    REQUIRE(output.find("=== SHAPE WITH MINIMUM PERIMETER ===") != std::string::npos);
    REQUIRE(output.find("Line [(0, 0) -> (0.5, 0.5)]") != std::string::npos);
    REQUIRE(output.find("Perimeter: 0.71") != std::string::npos);
}
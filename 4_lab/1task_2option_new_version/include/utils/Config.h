#pragma once

#include <string>

namespace Config
{
    const double DEFAULT = 0.0;
    
    // Форматы для ToString()
    const std::string LINE_FORMAT = "Line [(";
    const std::string CIRCLE_FORMAT = "Circle [center: (";
    const std::string TRIANGLE_FORMAT = "Triangle [(";
    const std::string RECTANGLE_FORMAT = "Rectangle [(";
    const std::string SQUARE_FORMAT = "Square [(";
    const std::string RHOMBUS_FORMAT = "Rhombus [(";
    const std::string PARALLELOGRAM_FORMAT = "Parallelogram [(";
    const std::string TRAPEZOID_FORMAT = "Trapezoid [(";
    
    const std::string COMMA_SPACE = ", ";
    const std::string CLOSE_PAREN = ")";
    const std::string CLOSE_BRACKET = ")]";
    const std::string ARROW = ") -> (";
    const std::string RADIUS_PREFIX = "), radius: ";
    const std::string COMMA_CLOSE = "), (";
}
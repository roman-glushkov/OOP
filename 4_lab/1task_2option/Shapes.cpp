#include "Shape.h"
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <array>

static double Distance(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

double Quadrilateral::Area() const {
    double area =
        p1.x * p2.y + p2.x * p3.y + p3.x * p4.y + p4.x * p1.y
      - p2.x * p1.y - p3.x * p2.y - p4.x * p3.y - p1.x * p4.y;

    return std::abs(area) / 2.0;
}

double Circle::Area() const {
    return PI * radius * radius;
}

double Triangle::Area() const {
    double area =
        p1.x * (p2.y - p3.y) +
        p2.x * (p3.y - p1.y) +
        p3.x * (p1.y - p2.y);

    return std::abs(area) / 2.0;
}

double Quadrilateral::Perimeter() const {
    return Distance(p1, p2) +
           Distance(p2, p3) +
           Distance(p3, p4) +
           Distance(p4, p1);
}

double Circle::Perimeter() const {
    return 2 * PI * radius;
}

double Triangle::Perimeter() const {
    return Distance(p1, p2) + Distance(p2, p3) + Distance(p3, p1);
}

double Line::Perimeter() const {
    return Distance(p1, p2);
}

std::string Quadrilateral::ToString() const {
    static const char* typeNames[] = {
        SHAPE_NAME_RECTANGLE.c_str(), 
        SHAPE_NAME_SQUARE.c_str(), 
        SHAPE_NAME_RHOMBUS.c_str(), 
        SHAPE_NAME_PARALLELOGRAM.c_str(), 
        SHAPE_NAME_TRAPEZOID.c_str()
    };
    
    std::ostringstream oss;
    oss << typeNames[static_cast<int>(type)] << FORMAT_QUADRILATERAL 
        << p1.x << FORMAT_COMMA_SPACE << p1.y << FORMAT_CLOSE_PAREN 
        << p2.x << FORMAT_COMMA_SPACE << p2.y << FORMAT_CLOSE_PAREN
        << p3.x << FORMAT_COMMA_SPACE << p3.y << FORMAT_CLOSE_PAREN 
        << p4.x << FORMAT_COMMA_SPACE << p4.y << FORMAT_CLOSE_BRACKET;
    return oss.str();
}

std::string Circle::ToString() const {
    std::ostringstream oss;
    oss << SHAPE_NAME_CIRCLE << FORMAT_CIRCLE_CENTER 
        << center.x << FORMAT_COMMA_SPACE << center.y 
        << FORMAT_CIRCLE_RADIUS << radius << "]";
    return oss.str();
}

std::string Triangle::ToString() const {
    std::ostringstream oss;
    oss << SHAPE_NAME_TRIANGLE << FORMAT_TRIANGLE_OPEN 
        << p1.x << FORMAT_COMMA_SPACE << p1.y << FORMAT_TRIANGLE_SEP
        << p2.x << FORMAT_COMMA_SPACE << p2.y << FORMAT_TRIANGLE_SEP
        << p3.x << FORMAT_COMMA_SPACE << p3.y << FORMAT_CLOSE_BRACKET;
    return oss.str();
}

std::string Line::ToString() const {
    std::ostringstream oss;
    oss << SHAPE_NAME_LINE << FORMAT_LINE_OPEN 
        << p1.x << FORMAT_COMMA_SPACE << p1.y << FORMAT_LINE_ARROW
        << p2.x << FORMAT_COMMA_SPACE << p2.y << FORMAT_CLOSE_BRACKET;
    return oss.str();
}
#include "shapes.h"
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <numeric>

static double Distance(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

double Quadrilateral::Area() const {
    switch(type) {
        case QuadrilateralType::Rectangle: case QuadrilateralType::Square:
        {
            return std::abs((p2.x - p1.x) * (p4.y - p1.y));
        }
            
        case QuadrilateralType::Rhombus:
        {
            return (Distance(p1, p3) * Distance(p2, p4)) / 2.0;
        }
            
        case QuadrilateralType::Parallelogram:
        {
            double base = Distance(p1, p2);
            double height = std::abs((p2.x - p1.x) * (p1.y - p4.y) - (p1.x - p4.x) * (p2.y - p1.y)) / base;
            return base * height;
        }
            
        case QuadrilateralType::Trapezoid:
        {
            double a = Distance(p1, p2);
            double b = Distance(p3, p4);
            double height = std::abs(p4.y - p1.y);
            return (a + b) * height / 2.0;
        }
    }
}

double Circle::Area() const {
    return M_PI * radius * radius;
}

double Triangle::Area() const {
    std::array<double, 3> sides = {
        Distance(p1, p2),
        Distance(p2, p3),
        Distance(p3, p1)
    };
    double s = std::accumulate(sides.begin(), sides.end(), 0.0) / 2.0;
    
    return std::sqrt(s * std::accumulate(sides.begin(), sides.end(), 1.0,
        [s](double product, double side) {
            return product * (s - side);
        }));
}

double Line::Area() const {
    return 0;
}

double Quadrilateral::Perimeter() const {
    std::array<double, 4> sides = {
        Distance(p1, p2),
        Distance(p2, p3),
        Distance(p3, p4),
        Distance(p4, p1)
    };
    
    switch(type) {
        case QuadrilateralType::Rectangle: case QuadrilateralType::Parallelogram:
        {
            return 2 * (sides[0] + sides[1]);
        }
            
        case QuadrilateralType::Square: case QuadrilateralType::Rhombus:
        {
            return 4 * sides[0];
        }
            
        case QuadrilateralType::Trapezoid:
        {
            return sides[0] + sides[1] + sides[2] + sides[3];
        }
    }
}

double Circle::Perimeter() const {
    return 2 * M_PI * radius;
}

double Triangle::Perimeter() const {
    return Distance(p1, p2) + Distance(p2, p3) + Distance(p3, p1);
}

double Line::Perimeter() const {
    return Distance(p1, p2);
}

std::string Quadrilateral::ToString() const {
    static const char* typeNames[] = {
        "Rectangle", "Square", "Rhombus", "Parallelogram", "Trapezoid"
    };
    
    std::ostringstream oss;
    oss << typeNames[static_cast<int>(type)] << " [(" 
        << p1.x << ", " << p1.y << "), (" << p2.x << ", " << p2.y << "), ("
        << p3.x << ", " << p3.y << "), (" << p4.x << ", " << p4.y << ")]";
    return oss.str();
}

std::string Circle::ToString() const {
    std::ostringstream oss;
    oss << "Circle [center: (" << center.x << ", " << center.y 
        << "), radius: " << radius << "]";
    return oss.str();
}

std::string Triangle::ToString() const {
    std::ostringstream oss;
    oss << "Triangle [(" << p1.x << ", " << p1.y << "), ("
        << p2.x << ", " << p2.y << "), (" << p3.x << ", " << p3.y << ")]";
    return oss.str();
}

std::string Line::ToString() const {
    std::ostringstream oss;
    oss << "Line [(" << p1.x << ", " << p1.y << ") -> ("
        << p2.x << ", " << p2.y << ")]";
    return oss.str();
}
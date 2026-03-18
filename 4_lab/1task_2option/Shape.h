#pragma once

#include <string>
#include <cmath>
#include <map>

// Default values
const double DEFAULT = 0.0;

// String constants
const std::string FILL_COLOR_NONE = "none";

// Shape names
const std::string SHAPE_NAME_RECTANGLE = "Rectangle";
const std::string SHAPE_NAME_SQUARE = "Square";
const std::string SHAPE_NAME_RHOMBUS = "Rhombus";
const std::string SHAPE_NAME_PARALLELOGRAM = "Parallelogram";
const std::string SHAPE_NAME_TRAPEZOID = "Trapezoid";
const std::string SHAPE_NAME_CIRCLE = "Circle";
const std::string SHAPE_NAME_TRIANGLE = "Triangle";
const std::string SHAPE_NAME_LINE = "Line";

// Format strings for ToString methods
const std::string FORMAT_QUADRILATERAL = " [(";
const std::string FORMAT_COMMA_SPACE = ", ";
const std::string FORMAT_CLOSE_PAREN = "), (";
const std::string FORMAT_CLOSE_BRACKET = ")]";
const std::string FORMAT_CIRCLE_CENTER = " [center: (";
const std::string FORMAT_CIRCLE_RADIUS = "), radius: ";
const std::string FORMAT_TRIANGLE_OPEN = " [(";
const std::string FORMAT_TRIANGLE_SEP = "), (";
const std::string FORMAT_LINE_ARROW = ") -> (";
const std::string FORMAT_LINE_OPEN = " [(";

// Math constants
const double PI = 3.14159265358979323846;

struct Point
{
    double x;
    double y;
    
    Point(double x = DEFAULT, double y = DEFAULT) : x(x), y(y) {}
};

class Shape
{
public:
    Shape(std::string outline, std::string fill) : outlineColor(outline), fillColor(fill) {}
    
    virtual ~Shape() = default; // удаление
    virtual double Area() const = 0; // площадь
    virtual double Perimeter() const = 0; // периметр
    virtual std::string ToString() const = 0; // сама строка

    std::string outlineColor;
    std::string fillColor; 
};

enum class QuadrilateralType {
    Rectangle,
    Square,
    Rhombus,
    Parallelogram,
    Trapezoid,
};

class Quadrilateral : public Shape
{
public:
    Quadrilateral(Point a, Point b, Point c, Point d, QuadrilateralType type, std::string outline, std::string fill) 
    : Shape(outline, fill), p1(a), p2(b), p3(c), p4(d), type(type) {}

    double Area() const override;
    double Perimeter() const override;
    std::string ToString() const override;

private:
    Point p1, p2, p3, p4;
    QuadrilateralType type;
};

class Circle : public Shape
{
public:
    Circle(Point c, double r, std::string outline, std::string fill) : Shape(outline, fill), center(c), radius(r) {}

    double Area() const override;
    double Perimeter() const override;
    std::string ToString() const override;

private:
    Point center;
    double radius;
};

class Triangle : public Shape
{
public:
    Triangle(Point a, Point b, Point c, std::string outline, std::string fill) : Shape(outline, fill), p1(a), p2(b), p3(c) {}

    double Area() const override;
    double Perimeter() const override;
    std::string ToString() const override;

private:
    Point p1, p2, p3;
};

class Line : public Shape
{
public:
    Line(Point a, Point b, std::string outline) : Shape(outline, FILL_COLOR_NONE), p1(a), p2(b) {}

    double Area() const override { return DEFAULT; }
    double Perimeter() const override;
    std::string ToString() const override;

private:
    Point p1, p2;
};
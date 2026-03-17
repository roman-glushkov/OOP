#pragma once

#include <string>
#include <cmath>

struct Point
{
    double x;
    double y;
};

class Shape
{
public:
    Shape(std::string outline, std::string fill) : outlineColor(outline), fillColor(fill) {}
    
    virtual ~Shape() = default; // удаление
    virtual double Area() const = 0; // площадь
    virtual double Perimeter() const = 0; // периметр
    virtual std::string ToString() const = 0; // сама строка

    std::string outlineColor; // цвет границы
    std::string fillColor; // цвет заливки
};

enum class QuadrilateralType {
    Rectangle, // прямоугольник
    Square, // квадрат
    Rhombus, // ромб
    Parallelogram, // паралелограмм
    Trapezoid, // трапеция
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
    Line(Point a, Point b, std::string outline) : Shape(outline, "none"), p1(a), p2(b) {}

    double Area() const override { return 0; }
    double Perimeter() const override;
    std::string ToString() const override;

private:
    Point p1, p2;
};
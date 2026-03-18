#include "ShapeController.h"
#include <iostream>     
#include <sstream>       
#include <iomanip>      
#include <algorithm> 
#include <cctype>    
#include <string>        

bool isValidColor(const std::string& color) {
    if (color.length() != COLOR_STRING_LENGTH) return false;
    for (char c : color) {
        if (!std::isxdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

std::shared_ptr<Shape> parseShape(const std::string& line) {
    std::istringstream iss(line);
    std::string type;

    if (!(iss >> type)) {
        std::cout << ERROR_PREFIX << ERROR_EMPTY_INPUT;
        return nullptr;
    }

    std::transform(type.begin(), type.end(), type.begin(), ::tolower);

    if (type == SHAPE_RECTANGLE || type == SHAPE_SQUARE || type == SHAPE_RHOMBUS ||
        type == SHAPE_PARALLELOGRAM || type == SHAPE_TRAPEZOID) {

        double x1, y1, x2, y2, x3, y3, x4, y4;
        std::string outline, fill;

        if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> outline >> fill)) {
            std::cout << ERROR_PREFIX << ERROR_INVALID_FORMAT;
            return nullptr;
        }

        if (!isValidColor(outline) || !isValidColor(fill)) {
            std::cout << ERROR_PREFIX << ERROR_INVALID_COLOR;
            return nullptr;
        }

        std::string extra;
        if (iss >> extra) {
            std::cout << ERROR_PREFIX << ERROR_EXTRA_DATA;
            return nullptr;
        }

        QuadrilateralType qType;
        if (type == SHAPE_RECTANGLE) qType = QuadrilateralType::Rectangle;
        else if (type == SHAPE_SQUARE) qType = QuadrilateralType::Square;
        else if (type == SHAPE_RHOMBUS) qType = QuadrilateralType::Rhombus;
        else if (type == SHAPE_PARALLELOGRAM) qType = QuadrilateralType::Parallelogram;
        else qType = QuadrilateralType::Trapezoid;

        return std::make_shared<Quadrilateral>(
            Point(x1, y1), Point(x2, y2), Point(x3, y3), Point(x4, y4),
            qType, outline, fill
        );
    }
    else if (type == SHAPE_CIRCLE) {
        double x, y, radius;
        std::string outline, fill;

        if (!(iss >> x >> y >> radius >> outline >> fill)) {
            std::cout << ERROR_PREFIX << ERROR_INVALID_FORMAT;
            return nullptr;
        }

        if (radius <= 0) {
            std::cout << ERROR_PREFIX << ERROR_INVALID_RADIUS;
            return nullptr;
        }

        if (!isValidColor(outline) || !isValidColor(fill)) {
            std::cout << ERROR_PREFIX << ERROR_INVALID_COLOR;
            return nullptr;
        }

        std::string extra;
        if (iss >> extra) {
            std::cout << ERROR_PREFIX << ERROR_EXTRA_DATA;
            return nullptr;
        }

        return std::make_shared<Circle>(Point(x, y), radius, outline, fill);
    }
    else if (type == SHAPE_TRIANGLE) {
        double x1, y1, x2, y2, x3, y3;
        std::string outline, fill;

        if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> outline >> fill)) {
            std::cout << ERROR_PREFIX << ERROR_INVALID_FORMAT;
            return nullptr;
        }

        if (!isValidColor(outline) || !isValidColor(fill)) {
            std::cout << ERROR_PREFIX << ERROR_INVALID_COLOR;
            return nullptr;
        }

        std::string extra;
        if (iss >> extra) {
            std::cout << ERROR_PREFIX << ERROR_EXTRA_DATA;
            return nullptr;
        }

        return std::make_shared<Triangle>(
            Point(x1, y1), Point(x2, y2), Point(x3, y3),
            outline, fill
        );
    }
    else if (type == SHAPE_LINE) {
        double x1, y1, x2, y2;
        std::string outline;

        if (!(iss >> x1 >> y1 >> x2 >> y2 >> outline)) {
            std::cout << ERROR_PREFIX << ERROR_INVALID_FORMAT;
            return nullptr;
        }

        if (!isValidColor(outline)) {
            std::cout << ERROR_PREFIX << ERROR_INVALID_COLOR;
            return nullptr;
        }

        std::string extra;
        if (iss >> extra) {
            std::cout << ERROR_PREFIX << ERROR_EXTRA_DATA;
            return nullptr;
        }

        return std::make_shared<Line>(
            Point(x1, y1), Point(x2, y2),
            outline
        );
    }

    std::cout << ERROR_PREFIX << ERROR_UNKNOWN_TYPE;
    return nullptr;
}

std::shared_ptr<Shape> findMaxArea(const std::vector<std::shared_ptr<Shape>>& shapes) {
    if (shapes.empty()) return nullptr;

    auto maxShape = shapes[0];
    for (const auto& shape : shapes) {
        if (shape->Area() > maxShape->Area()) {
            maxShape = shape;
        }
    }
    return maxShape;
}

std::shared_ptr<Shape> findMinPerimeter(const std::vector<std::shared_ptr<Shape>>& shapes) {
    if (shapes.empty()) return nullptr;

    auto minShape = shapes[0];
    for (const auto& shape : shapes) {
        if (shape->Perimeter() < minShape->Perimeter()) {
            minShape = shape;
        }
    }
    return minShape;
}

void printShapeInfo(const std::shared_ptr<Shape>& shape, const std::string& title) {
    if (!shape) return;

    std::cout << OUTPUT_TITLE_PREFIX << title << OUTPUT_TITLE_SUFFIX;
    std::cout << shape->ToString() << NEWLINE;
    std::cout << OUTPUT_AREA << std::fixed << std::setprecision(OUTPUT_PRECISION) << shape->Area() << NEWLINE;
    std::cout << OUTPUT_PERIMETER << std::fixed << std::setprecision(OUTPUT_PRECISION) << shape->Perimeter() << NEWLINE;
    std::cout << OUTPUT_OUTLINE_COLOR << shape->outlineColor << NEWLINE;

    if (shape->fillColor != OUTPUT_FILL_COLOR_NONE) {
        std::cout << OUTPUT_FILL_COLOR << shape->fillColor << NEWLINE;
    }
}
#include "../../include/utils/ShapeParser.h"      // было #include "ShapeParser.h"
#include "../../include/utils/Config.h"           // было #include "Config.h"
#include "../../include/shapes/CLineSegment.h"
#include "shapes/CTriangle.h"
#include "shapes/CRectangle.h"
#include "shapes/CCircle.h"
#include "shapes/CSquare.h"
#include "shapes/CRhombus.h"
#include "shapes/CParallelogram.h"
#include "shapes/CTrapezoid.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <iomanip>

bool ShapeParser::IsValidColor(const std::string& color)
{
    if (color.length() != Config::COLOR_STRING_LENGTH) return false;
    for (char c : color) {
        if (!std::isxdigit(c)) return false;
    }
    return true;
}

uint32_t ShapeParser::ColorStringToUint32(const std::string& color)
{
    return std::stoul(color, nullptr, 16);
}

std::shared_ptr<IShape> ShapeParser::ParseShape(const std::string& line)
{
    std::istringstream iss(line);
    std::string type;
    
    if (!(iss >> type)) {
        std::cout << Config::ERROR_PREFIX << Config::ERROR_EMPTY_INPUT;
        return nullptr;
    }
    
    std::transform(type.begin(), type.end(), type.begin(), ::tolower);
    
    // Парсинг линии (отрезка)
    if (type == Config::SHAPE_LINE) {
        double x1, y1, x2, y2;
        std::string outlineColorStr;
        
        if (!(iss >> x1 >> y1 >> x2 >> y2 >> outlineColorStr)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_FORMAT;
            return nullptr;
        }
        
        if (!IsValidColor(outlineColorStr)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_COLOR;
            return nullptr;
        }
        
        std::string extra;
        if (iss >> extra) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_EXTRA_DATA;
            return nullptr;
        }
        
        uint32_t outlineColor = ColorStringToUint32(outlineColorStr);
        return std::make_shared<CLineSegment>(CPoint(x1, y1), CPoint(x2, y2), outlineColor);
    }
    
    // Парсинг треугольника
    if (type == Config::SHAPE_TRIANGLE) {
        double x1, y1, x2, y2, x3, y3;
        std::string outlineColorStr, fillColorStr;
        
        if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> outlineColorStr >> fillColorStr)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_FORMAT;
            return nullptr;
        }
        
        if (!IsValidColor(outlineColorStr) || !IsValidColor(fillColorStr)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_COLOR;
            return nullptr;
        }
        
        std::string extra;
        if (iss >> extra) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_EXTRA_DATA;
            return nullptr;
        }
        
        uint32_t outlineColor = ColorStringToUint32(outlineColorStr);
        uint32_t fillColor = ColorStringToUint32(fillColorStr);
        
        return std::make_shared<CTriangle>(CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3), outlineColor, fillColor);
    }
    
    // Парсинг прямоугольника
    if (type == Config::SHAPE_RECTANGLE) {
        double x, y, width, height;
        std::string outlineColorStr, fillColorStr;
        
        if (!(iss >> x >> y >> width >> height >> outlineColorStr >> fillColorStr)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_FORMAT;
            return nullptr;
        }
        
        if (!IsValidColor(outlineColorStr) || !IsValidColor(fillColorStr)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_COLOR;
            return nullptr;
        }
        
        std::string extra;
        if (iss >> extra) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_EXTRA_DATA;
            return nullptr;
        }
        
        uint32_t outlineColor = ColorStringToUint32(outlineColorStr);
        uint32_t fillColor = ColorStringToUint32(fillColorStr);
        
        return std::make_shared<CRectangle>(CPoint(x, y), width, height, outlineColor, fillColor);
    }
    
    // Парсинг круга
    if (type == Config::SHAPE_CIRCLE) {
        double x, y, radius;
        std::string outlineColorStr, fillColorStr;
        
        if (!(iss >> x >> y >> radius >> outlineColorStr >> fillColorStr)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_FORMAT;
            return nullptr;
        }
        
        if (radius <= 0) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_RADIUS;
            return nullptr;
        }
        
        if (!IsValidColor(outlineColorStr) || !IsValidColor(fillColorStr)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_COLOR;
            return nullptr;
        }
        
        std::string extra;
        if (iss >> extra) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_EXTRA_DATA;
            return nullptr;
        }
        
        uint32_t outlineColor = ColorStringToUint32(outlineColorStr);
        uint32_t fillColor = ColorStringToUint32(fillColorStr);
        
        return std::make_shared<CCircle>(CPoint(x, y), radius, outlineColor, fillColor);
    }
    
    // Парсинг квадрата
    if (type == Config::SHAPE_SQUARE) {
        double x, y, side;
        std::string outlineColorStr, fillColorStr;
        
        if (!(iss >> x >> y >> side >> outlineColorStr >> fillColorStr)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_FORMAT;
            return nullptr;
        }
        
        if (!IsValidColor(outlineColorStr) || !IsValidColor(fillColorStr)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_COLOR;
            return nullptr;
        }
        
        std::string extra;
        if (iss >> extra) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_EXTRA_DATA;
            return nullptr;
        }
        
        uint32_t outlineColor = ColorStringToUint32(outlineColorStr);
        uint32_t fillColor = ColorStringToUint32(fillColorStr);
        
        return std::make_shared<CSquare>(CPoint(x, y), side, outlineColor, fillColor);
    }
    
    // Парсинг ромба
    if (type == Config::SHAPE_RHOMBUS) {
        double x, y, diag1, diag2;
        std::string outlineColorStr, fillColorStr;
        
        if (!(iss >> x >> y >> diag1 >> diag2 >> outlineColorStr >> fillColorStr)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_FORMAT;
            return nullptr;
        }
        
        if (!IsValidColor(outlineColorStr) || !IsValidColor(fillColorStr)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_COLOR;
            return nullptr;
        }
        
        std::string extra;
        if (iss >> extra) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_EXTRA_DATA;
            return nullptr;
        }
        
        uint32_t outlineColor = ColorStringToUint32(outlineColorStr);
        uint32_t fillColor = ColorStringToUint32(fillColorStr);
        
        return std::make_shared<CRhombus>(CPoint(x, y), diag1, diag2, outlineColor, fillColor);
    }
    
    // Парсинг параллелограмма
    if (type == Config::SHAPE_PARALLELOGRAM) {
        double x1, y1, x2, y2, x3, y3;
        std::string outlineColorStr, fillColorStr;
        
        if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> outlineColorStr >> fillColorStr)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_FORMAT;
            return nullptr;
        }
        
        if (!IsValidColor(outlineColorStr) || !IsValidColor(fillColorStr)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_COLOR;
            return nullptr;
        }
        
        std::string extra;
        if (iss >> extra) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_EXTRA_DATA;
            return nullptr;
        }
        
        uint32_t outlineColor = ColorStringToUint32(outlineColorStr);
        uint32_t fillColor = ColorStringToUint32(fillColorStr);
        
        return std::make_shared<CParallelogram>(CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3), outlineColor, fillColor);
    }
    
    // Парсинг трапеции
    if (type == Config::SHAPE_TRAPEZOID) {
        double x1, y1, x2, y2, x3, y3, x4, y4;
        std::string outlineColorStr, fillColorStr;
        
        if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> outlineColorStr >> fillColorStr)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_FORMAT;
            return nullptr;
        }
        
        if (!IsValidColor(outlineColorStr) || !IsValidColor(fillColorStr)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_COLOR;
            return nullptr;
        }
        
        std::string extra;
        if (iss >> extra) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_EXTRA_DATA;
            return nullptr;
        }
        
        uint32_t outlineColor = ColorStringToUint32(outlineColorStr);
        uint32_t fillColor = ColorStringToUint32(fillColorStr);
        
        return std::make_shared<CTrapezoid>(CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3), CPoint(x4, y4), outlineColor, fillColor);
    }
    
    std::cout << Config::ERROR_PREFIX << Config::ERROR_UNKNOWN_TYPE;
    return nullptr;
}
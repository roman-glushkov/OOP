#include "../../include/utils/ShapeController.h"
#include "../../include/utils/ShapeParser.h"  
#include "../../include/utils/Config.h"       
#include "../../include/interfaces/ISolidShape.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

void ShapeController::ReadShapes()
{
    std::cout << Config::PROMPT_ENTER_SHAPES;
    
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        
        auto shape = ShapeParser::ParseShape(line);
        if (shape) {
            m_shapes.push_back(shape);
            std::cout << Config::MSG_ADDED_PREFIX << shape->ToString() << std::endl;
        }
    }
}

std::shared_ptr<IShape> ShapeController::FindMaxArea() const
{
    if (m_shapes.empty()) return nullptr;
    
    auto it = std::max_element(m_shapes.begin(), m_shapes.end(),
        [](const auto& a, const auto& b) {
            return a->GetArea() < b->GetArea();
        });
    
    return *it;
}

std::shared_ptr<IShape> ShapeController::FindMinPerimeter() const
{
    if (m_shapes.empty()) return nullptr;
    
    auto it = std::min_element(m_shapes.begin(), m_shapes.end(),
        [](const auto& a, const auto& b) {
            return a->GetPerimeter() < b->GetPerimeter();
        });
    
    return *it;
}

void ShapeController::PrintShapeInfo(const std::shared_ptr<IShape>& shape, const std::string& title) const
{
    if (!shape) return;
    
    std::cout << Config::OUTPUT_TITLE_PREFIX << title << Config::OUTPUT_TITLE_SUFFIX;
    std::cout << shape->ToString() << Config::NEWLINE;
    
    std::cout << Config::OUTPUT_AREA 
              << std::fixed << std::setprecision(Config::OUTPUT_PRECISION) 
              << shape->GetArea() << Config::NEWLINE;
    
    std::cout << Config::OUTPUT_PERIMETER 
              << std::fixed << std::setprecision(Config::OUTPUT_PRECISION) 
              << shape->GetPerimeter() << Config::NEWLINE;

    uint32_t outlineColor = shape->GetOutlineColor();
    std::cout << Config::OUTPUT_OUTLINE_COLOR 
              << std::hex << std::setfill('0') << std::setw(6) 
              << outlineColor << std::dec << Config::NEWLINE;

    auto solidShape = std::dynamic_pointer_cast<ISolidShape>(shape);
    if (solidShape) {
        uint32_t fillColor = solidShape->GetFillColor();
        std::cout << Config::OUTPUT_FILL_COLOR 
                  << std::hex << std::setfill('0') << std::setw(6) 
                  << fillColor << std::dec << Config::NEWLINE;
    }
}

void ShapeController::PrintResults() const
{
    if (m_shapes.empty()) {
        std::cout << Config::MSG_NO_SHAPES;
        return;
    }
    
    std::cout << Config::MSG_TOTAL_SHAPES << m_shapes.size() << Config::MSG_SEPARATOR;
    
    auto maxAreaShape = FindMaxArea();
    PrintShapeInfo(maxAreaShape, Config::TITLE_MAX_AREA);
    
    auto minPerimeterShape = FindMinPerimeter();
    PrintShapeInfo(minPerimeterShape, Config::TITLE_MIN_PERIMETER);
}
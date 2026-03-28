#pragma once
#include <string>
#include <vector>
#include <memory>
#include "interfaces/IShape.h"

class ShapeController
{
public:
    void ReadShapes();
    void PrintResults() const;
    
private:
    std::vector<std::shared_ptr<IShape>> m_shapes;
    std::shared_ptr<IShape> FindMaxArea() const;
    std::shared_ptr<IShape> FindMinPerimeter() const;
    void PrintShapeInfo(const std::shared_ptr<IShape>& shape, const std::string& title) const;
};
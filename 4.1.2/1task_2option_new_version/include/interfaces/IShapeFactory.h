#pragma once
#include <memory>
#include <string>
#include "IShape.h"

class IShapeFactory
{
public:
    virtual ~IShapeFactory() = default;
    
    // Создаёт фигуру из строки параметров
    virtual std::shared_ptr<IShape> Create(const std::string& params) const = 0;
    
    // Возвращает тип фигуры (для регистрации)
    virtual std::string GetType() const = 0;
};
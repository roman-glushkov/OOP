#pragma once

#include <string>
#include <memory>
#include "../interfaces/IShape.h"

class ShapeParser
{
public:
    static std::shared_ptr<IShape> ParseShape(const std::string& line);
    
private:
    static bool IsValidColor(const std::string& color);
    static uint32_t ColorStringToUint32(const std::string& color);
};
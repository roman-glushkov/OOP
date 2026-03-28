#include "../../include/interfaces/IShapeFactory.h"
#include "../../include/shapes/CLineSegment.h"
#include "../../include/utils/Config.h"
#include <sstream>
#include <iostream>
#include <cctype>

class LineFactory : public IShapeFactory
{
private:
    bool IsValidColor(const std::string& color) const
    {
        if (color.length() != Config::COLOR_STRING_LENGTH) return false;
        for (char c : color) {
            if (!std::isxdigit(c)) return false;
        }
        return true;
    }
    
    bool HasExtraData(std::istringstream& iss) const
    {
        std::string extra;
        if (iss >> extra) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_EXTRA_DATA;
            return true;
        }
        return false;
    }
    
public:
    std::shared_ptr<IShape> Create(const std::string& params) const override
    {
        std::istringstream iss(params);
        
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
        
        if (HasExtraData(iss)) {
            return nullptr;
        }
        
        uint32_t outlineColor = std::stoul(outlineColorStr, nullptr, 16);
        return std::make_shared<CLineSegment>(CPoint(x1, y1), CPoint(x2, y2), outlineColor);
    }
    
    std::string GetType() const override
    {
        return Config::SHAPE_LINE;
    }
};

std::shared_ptr<IShapeFactory> CreateLineFactory()
{
    return std::make_shared<LineFactory>();
}
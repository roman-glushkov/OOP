#include "../../include/utils/SolidShapeFactory.h"
#include "../../include/shapes/CCircle.h"
#include "../../include/utils/Config.h"
#include <sstream>
#include <iostream>

class CircleFactory : public SolidShapeFactory
{
public:
    std::shared_ptr<IShape> Create(const std::string& params) const override
    {
        std::istringstream iss(params);
        
        double x, y, radius;
        uint32_t outlineColor, fillColor;
        
        if (!(iss >> x >> y >> radius)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_FORMAT;
            return nullptr;
        }
        
        if (radius <= 0) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_RADIUS;
            return nullptr;
        }
        
        if (!ReadAndConvertColors(iss, outlineColor, fillColor)) {
            return nullptr;
        }
        
        if (HasExtraData(iss)) {
            return nullptr;
        }
        
        return std::make_shared<CCircle>(CPoint(x, y), radius, outlineColor, fillColor);
    }
    
    std::string GetType() const override
    {
        return Config::SHAPE_CIRCLE;
    }
};

std::shared_ptr<IShapeFactory> CreateCircleFactory()
{
    return std::make_shared<CircleFactory>();
}
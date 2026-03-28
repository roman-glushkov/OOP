#include "../../include/utils/SolidShapeFactory.h"
#include "../../include/shapes/CRectangle.h"
#include "../../include/utils/Config.h"
#include <sstream>

class RectangleFactory : public SolidShapeFactory
{
public:
    std::shared_ptr<IShape> Create(const std::string& params) const override
    {
        std::istringstream iss(params);
        
        double x, y, width, height;
        uint32_t outlineColor, fillColor;
        
        if (!(iss >> x >> y >> width >> height)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_FORMAT;
            return nullptr;
        }
        
        if (!ReadAndConvertColors(iss, outlineColor, fillColor)) {
            return nullptr;
        }
        
        if (HasExtraData(iss)) {
            return nullptr;
        }
        
        return std::make_shared<CRectangle>(CPoint(x, y), width, height, outlineColor, fillColor);
    }
    
    std::string GetType() const override
    {
        return Config::SHAPE_RECTANGLE;
    }
};

std::shared_ptr<IShapeFactory> CreateRectangleFactory()
{
    return std::make_shared<RectangleFactory>();
}
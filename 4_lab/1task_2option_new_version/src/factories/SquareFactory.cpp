#include "../../include/utils/SolidShapeFactory.h"
#include "../../include/shapes/CSquare.h"
#include "../../include/utils/Config.h"
#include <sstream>

class SquareFactory : public SolidShapeFactory
{
public:
    std::shared_ptr<IShape> Create(const std::string& params) const override
    {
        std::istringstream iss(params);
        
        double x, y, side;
        uint32_t outlineColor, fillColor;
        
        if (!(iss >> x >> y >> side)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_FORMAT;
            return nullptr;
        }
        
        if (!ReadAndConvertColors(iss, outlineColor, fillColor)) {
            return nullptr;
        }
        
        if (HasExtraData(iss)) {
            return nullptr;
        }
        
        return std::make_shared<CSquare>(CPoint(x, y), side, outlineColor, fillColor);
    }
    
    std::string GetType() const override
    {
        return Config::SHAPE_SQUARE;
    }
};

std::shared_ptr<IShapeFactory> CreateSquareFactory()
{
    return std::make_shared<SquareFactory>();
}
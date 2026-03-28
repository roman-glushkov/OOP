#include "../../include/utils/SolidShapeFactory.h"
#include "../../include/shapes/CRhombus.h"
#include "../../include/utils/Config.h"
#include <sstream>

class RhombusFactory : public SolidShapeFactory
{
public:
    std::shared_ptr<IShape> Create(const std::string& params) const override
    {
        std::istringstream iss(params);
        
        double x, y, diag1, diag2;
        uint32_t outlineColor, fillColor;
        
        if (!(iss >> x >> y >> diag1 >> diag2)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_FORMAT;
            return nullptr;
        }
        
        if (!ReadAndConvertColors(iss, outlineColor, fillColor)) {
            return nullptr;
        }
        
        if (HasExtraData(iss)) {
            return nullptr;
        }
        
        return std::make_shared<CRhombus>(CPoint(x, y), diag1, diag2, outlineColor, fillColor);
    }
    
    std::string GetType() const override
    {
        return Config::SHAPE_RHOMBUS;
    }
};

std::shared_ptr<IShapeFactory> CreateRhombusFactory()
{
    return std::make_shared<RhombusFactory>();
}
#include "../../include/utils/SolidShapeFactory.h"
#include "../../include/shapes/CParallelogram.h"
#include "../../include/utils/Config.h"
#include <sstream>

class ParallelogramFactory : public SolidShapeFactory
{
public:
    std::shared_ptr<IShape> Create(const std::string& params) const override
    {
        std::istringstream iss(params);
        
        double x1, y1, x2, y2, x3, y3;
        uint32_t outlineColor, fillColor;
        
        if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_FORMAT;
            return nullptr;
        }
        
        if (!ReadAndConvertColors(iss, outlineColor, fillColor)) {
            return nullptr;
        }
        
        if (HasExtraData(iss)) {
            return nullptr;
        }
        
        return std::make_shared<CParallelogram>(
            CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3),
            outlineColor, fillColor
        );
    }
    
    std::string GetType() const override
    {
        return Config::SHAPE_PARALLELOGRAM;
    }
};

std::shared_ptr<IShapeFactory> CreateParallelogramFactory()
{
    return std::make_shared<ParallelogramFactory>();
}
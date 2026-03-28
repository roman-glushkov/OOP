#include "../../include/interfaces/IShapeFactory.h"
#include <unordered_map>
#include <memory>
#include <string>

std::shared_ptr<IShapeFactory> CreateLineFactory();
std::shared_ptr<IShapeFactory> CreateTriangleFactory();
std::shared_ptr<IShapeFactory> CreateRectangleFactory();
std::shared_ptr<IShapeFactory> CreateCircleFactory();
std::shared_ptr<IShapeFactory> CreateSquareFactory();
std::shared_ptr<IShapeFactory> CreateRhombusFactory();
std::shared_ptr<IShapeFactory> CreateParallelogramFactory();
std::shared_ptr<IShapeFactory> CreateTrapezoidFactory();

std::unordered_map<std::string, std::shared_ptr<IShapeFactory>> GetAllFactories()
{
    std::unordered_map<std::string, std::shared_ptr<IShapeFactory>> factories;
    
    factories[Config::SHAPE_LINE] = CreateLineFactory();
    factories[Config::SHAPE_TRIANGLE] = CreateTriangleFactory();
    factories[Config::SHAPE_RECTANGLE] = CreateRectangleFactory();
    factories[Config::SHAPE_CIRCLE] = CreateCircleFactory();
    factories[Config::SHAPE_SQUARE] = CreateSquareFactory();
    factories[Config::SHAPE_RHOMBUS] = CreateRhombusFactory();
    factories[Config::SHAPE_PARALLELOGRAM] = CreateParallelogramFactory();
    factories[Config::SHAPE_TRAPEZOID] = CreateTrapezoidFactory();
    
    return factories;
}
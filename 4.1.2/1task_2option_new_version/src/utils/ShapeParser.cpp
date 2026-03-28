#include "../../include/utils/ShapeParser.h"
#include "../../include/utils/Config.h"
#include "../../include/interfaces/IShapeFactory.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <unordered_map>

std::unordered_map<std::string, std::shared_ptr<IShapeFactory>> GetAllFactories();

static std::unordered_map<std::string, std::shared_ptr<IShapeFactory>> s_factories;
static bool s_initialized = false;

static void InitializeFactories()
{
    if (s_initialized) return;
    s_factories = GetAllFactories();
    s_initialized = true;
}

std::shared_ptr<IShape> ShapeParser::ParseShape(const std::string& line)
{
    InitializeFactories();
    
    std::istringstream iss(line);
    std::string type;
    
    if (!(iss >> type)) {
        std::cout << Config::ERROR_PREFIX << Config::ERROR_EMPTY_INPUT;
        return nullptr;
    }
    
    std::transform(type.begin(), type.end(), type.begin(), ::tolower);
    
    auto it = s_factories.find(type);
    if (it == s_factories.end()) {
        std::cout << Config::ERROR_PREFIX << Config::ERROR_UNKNOWN_TYPE;
        return nullptr;
    }
    
    std::string params;
    std::getline(iss, params);
    if (!params.empty() && params[0] == ' ') {
        params = params.substr(1);
    }
    
    return it->second->Create(params);
}

bool ShapeParser::IsValidColor(const std::string& color)
{
    if (color.length() != Config::COLOR_STRING_LENGTH) return false;
    for (char c : color) {
        if (!std::isxdigit(c)) return false;
    }
    return true;
}

uint32_t ShapeParser::ColorStringToUint32(const std::string& color)
{
    return std::stoul(color, nullptr, 16);
}
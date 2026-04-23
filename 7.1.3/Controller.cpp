#include "Controller.h"
#include "FindMaxEx.h"
#include "Config.h"
#include <iostream> // std::cout
#include <vector> // std::vector
#include <string> // std::string
#include <sstream> // std::ostringstream
#include <stdexcept> // std::invalid_argument

Athlete::Athlete(const std::string& name, double h, double w) 
    : fullName(name), height(h), weight(w)
{
    if (h <= 0) 
    {
        throw std::invalid_argument(Config::ERROR_HEIGHT_POSITIVE);
    }
    if (w <= 0) 
    {
        throw std::invalid_argument(Config::ERROR_WEIGHT_POSITIVE);
    }
}

Athlete::Athlete() : fullName(""), height(0), weight(0) {}

std::string Controller::ProcessCommands(const std::vector<Athlete>& athletes)  
{
    std::ostringstream output;
    
    if (athletes.empty()) 
    {
        output << Config::ERROR_EMPTY_ARRAY << std::endl;
        return output.str();
    }
    
    Athlete result;
    
    output << Config::MSG_SEARCH_HEIGHT << std::endl;
    if (FindMaxEx(athletes, result, [](const Athlete& a, const Athlete& b) {
        return a.height < b.height;
    }))
    {
        output << result.fullName
               << Config::SEPARATOR
               << result.height << " " << Config::UNIT_HEIGHT
               << Config::SEPARATOR
               << result.weight << " " << Config::UNIT_WEIGHT
               << std::endl;
    }

    output << std::endl;

    output << Config::MSG_SEARCH_WEIGHT << std::endl;
    if (FindMaxEx(athletes, result, [](const Athlete& a, const Athlete& b) {
        return a.weight < b.weight;
    }))
    {
        output << result.fullName
               << Config::SEPARATOR
               << result.height << " " << Config::UNIT_HEIGHT
               << Config::SEPARATOR
               << result.weight << " " << Config::UNIT_WEIGHT
               << std::endl;
    }
    
    return output.str();
}
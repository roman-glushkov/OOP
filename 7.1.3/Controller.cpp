#include "Controller.h"
#include "FindMaxEx.h"
#include "Config.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

struct Athlete
{
    std::string fullName;
    double height;
    double weight;
    
    Athlete(const std::string& name, double h, double w)
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
    
    Athlete() : fullName(""), height(0), weight(0) {}
};

struct CompareByHeight
{
    bool operator()(const Athlete& a, const Athlete& b) const
    {
        return a.height < b.height;
    }
};

struct CompareByWeight
{
    bool operator()(const Athlete& a, const Athlete& b) const
    {
        return a.weight < b.weight;
    }
};

static std::vector<Athlete> LoadAthletes()
{
    std::vector<Athlete> athletes;
    std::ifstream file(Config::DATABASE_FILE);
    
    if (!file.is_open())
    {
        std::cout << Config::ERROR_FILE_NOT_OPEN << std::endl;
        return athletes;
    }
    
    std::string line;
    int lineNumber = 1;
    
    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string name;
        double height, weight;
        
        std::getline(ss, name, Config::DELIMITER);
        ss >> height;
        ss.ignore(Config::IGNORE_COUNT, Config::DELIMITER);
        ss >> weight;
        
        try
        {
            athletes.push_back(Athlete(name, height, weight));
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << Config::ERROR_PREFIX << "Line " << lineNumber << ": " << e.what() << std::endl;
        }
        
        lineNumber++;
    }
    
    return athletes;
}

void Controller::ProcessCommands()
{
    std::vector<Athlete> athletes = LoadAthletes();
    
    if (athletes.empty())
    {
        std::cout << Config::ERROR_EMPTY_ARRAY << std::endl;
        return;
    }
    
    Athlete result;
    
    std::cout << Config::MSG_SEARCH_HEIGHT << std::endl;
    if (FindMaxEx(athletes, result, CompareByHeight()))
    {
        std::cout << result.fullName
                  << Config::SEPARATOR
                  << result.height << " " << Config::UNIT_HEIGHT
                  << Config::SEPARATOR
                  << result.weight << " " << Config::UNIT_WEIGHT
                  << std::endl;
    }
    
    std::cout << std::endl;
    
    std::cout << Config::MSG_SEARCH_WEIGHT << std::endl;
    if (FindMaxEx(athletes, result, CompareByWeight()))
    {
        std::cout << result.fullName
                  << Config::SEPARATOR
                  << result.height << " " << Config::UNIT_HEIGHT
                  << Config::SEPARATOR
                  << result.weight << " " << Config::UNIT_WEIGHT
                  << std::endl;
    }
}
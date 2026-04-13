#include "Controller.h"
#include "FindMaxEx.h"
#include "Config.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

struct Athlete
{
    std::string fullName;
    double height;
    double weight;
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
    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        Athlete a;

        std::getline(ss, a.fullName, Config::DELIMITER);
        ss >> a.height;
        ss.ignore(Config::IGNORE_COUNT, Config::DELIMITER);
        ss >> a.weight;

        athletes.push_back(a);
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
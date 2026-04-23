#pragma once
#include <vector>
#include <string>

struct Athlete 
{
    std::string fullName; 
    double height; 
    double weight; 
    
    Athlete(const std::string& name, double h, double w);
    Athlete();
};

class Controller
{
public:
    static std::string ProcessCommands(const std::vector<Athlete>& athletes);
};
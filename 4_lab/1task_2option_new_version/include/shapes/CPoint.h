#pragma once
#include "../utils/Config.h"

class CPoint
{
public:
    double x;
    double y;
    
    CPoint(double x = Config::DEFAULT, double y = Config::DEFAULT) : x(x), y(y) {}
};
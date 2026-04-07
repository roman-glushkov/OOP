#define SOLVE3_H

#include "Config.h"

struct EquationRoots3
{
    int numRoots;
    double roots[Config::THREE];
};

EquationRoots3 Solve3(double a, double b, double c, double d);
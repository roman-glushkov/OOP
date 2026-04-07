#include <cmath>
#include <stdexcept>
#include <algorithm>
#include "Config.h"

struct EquationRoots3
{
    int numRoots;
    double roots[3];
};

static double solveCubicCardano(double a, double b, double c, double d, double roots[])
{
    if (a == Config::ZERO)
        throw std::invalid_argument(Config::ERROR_COEFFICIENT_ZERO);
    
    double A = b / a;
    double B = c / a;
    double C = d / a;
    
    double p = B - A * A / Config::THREE;
    double q = (Config::TWO * A * A * A) / Config::DIV_BY_27 - (A * B) / Config::THREE + C;
    
    double discriminant = (q * q) / Config::FOUR + (p * p * p) / Config::DIV_BY_27;
    
    int numRoots = Config::ZERO;
    
    if (discriminant > Config::EPSILON)
    {
        double sqrtD = sqrt(discriminant);
        double u = cbrt(-q / Config::TWO + sqrtD);
        double v = cbrt(-q / Config::TWO - sqrtD);
        double y1 = u + v;
        double x1 = y1 - A / Config::THREE;
        roots[numRoots++] = x1;
    }
    else if (fabs(discriminant) < Config::EPSILON)
    {
        double u = cbrt(-q / Config::TWO);
        double y1 = Config::TWO * u;
        double y2 = -u;
        
        double x1 = y1 - A / Config::THREE;
        double x2 = y2 - A / Config::THREE;
        
        if (fabs(x1 - x2) > Config::ROUNDING_EPSILON)
        {
            roots[numRoots++] = x1;
            roots[numRoots++] = x2;
        }
        else
        {
            roots[numRoots++] = x1;
        }
    }
    else
    {
        double r = sqrt(-p * p * p / Config::DIV_BY_27);
        double phi = acos(-q / (Config::TWO * r));
        double y1 = Config::TWO * cbrt(r) * cos(phi / Config::THREE);
        double y2 = Config::TWO * cbrt(r) * cos((phi + Config::TWO_PI) / Config::THREE);
        double y3 = Config::TWO * cbrt(r) * cos((phi + Config::FOUR_PI) / Config::THREE);
        
        double x1 = y1 - A / Config::THREE;
        double x2 = y2 - A / Config::THREE;
        double x3 = y3 - A / Config::THREE;
        
        roots[numRoots++] = x1;
        roots[numRoots++] = x2;
        roots[numRoots++] = x3;
    }
    
    std::sort(roots, roots + numRoots);

    int uniqueCount = numRoots;
    for (int i = Config::ZERO; i < uniqueCount - Config::ONE; i++)
    {
        if (fabs(roots[i] - roots[i + Config::ONE]) < Config::ROUNDING_EPSILON)
        {
            for (int j = i + Config::ONE; j < uniqueCount - Config::ONE; j++)
                roots[j] = roots[j + Config::ONE];
            uniqueCount--;
            i--;
        }
    }
    
    for (int i = Config::ZERO; i < uniqueCount; i++)
    {
        double rounded = round(roots[i]);
        if (fabs(roots[i] - rounded) < Config::ROUND_THRESHOLD)
        {
            roots[i] = rounded;
        }
    }
    
    return uniqueCount;
}

EquationRoots3 Solve3(double a, double b, double c, double d)
{
    EquationRoots3 result;
    result.numRoots = solveCubicCardano(a, b, c, d, result.roots);
    return result;
}
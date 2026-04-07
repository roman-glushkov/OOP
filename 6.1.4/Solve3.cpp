#include <cmath>
#include <stdexcept>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct EquationRoots3
{
    int numRoots;
    double roots[3];
};

static double solveCubicCardano(double a, double b, double c, double d, double roots[])
{
    if (a == 0)
        throw std::invalid_argument("Coefficient at x^3 cannot be zero");
    
    double A = b / a;
    double B = c / a;
    double C = d / a;
    
    double p = B - A*A / 3;
    double q = (2*A*A*A) / 27 - (A*B) / 3 + C;
    
    double discriminant = (q*q) / 4 + (p*p*p) / 27;
    
    int numRoots = 0;
    
    if (discriminant > 1e-12)
    {
        double sqrtD = sqrt(discriminant);
        double u = cbrt(-q/2 + sqrtD);
        double v = cbrt(-q/2 - sqrtD);
        double y1 = u + v;
        double x1 = y1 - A/3;
        roots[numRoots++] = x1;
    }
    else if (fabs(discriminant) < 1e-12)
    {
        double u = cbrt(-q/2);
        double y1 = 2*u;
        double y2 = -u;
        
        double x1 = y1 - A/3;
        double x2 = y2 - A/3;
        
        if (fabs(x1 - x2) > 1e-9)
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
        double r = sqrt(-p*p*p/27);
        double phi = acos(-q/(2*r));
        double y1 = 2 * cbrt(r) * cos(phi/3);
        double y2 = 2 * cbrt(r) * cos((phi + 2*M_PI)/3);
        double y3 = 2 * cbrt(r) * cos((phi + 4*M_PI)/3);
        
        double x1 = y1 - A/3;
        double x2 = y2 - A/3;
        double x3 = y3 - A/3;
        
        roots[numRoots++] = x1;
        roots[numRoots++] = x2;
        roots[numRoots++] = x3;
    }
    
    std::sort(roots, roots + numRoots);

    int uniqueCount = numRoots;
    for (int i = 0; i < uniqueCount - 1; i++)
    {
        if (fabs(roots[i] - roots[i+1]) < 1e-9)
        {
            for (int j = i+1; j < uniqueCount - 1; j++)
                roots[j] = roots[j+1];
            uniqueCount--;
            i--;
        }
    }
    
    for (int i = 0; i < uniqueCount; i++)
    {
        double rounded = round(roots[i]);
        if (fabs(roots[i] - rounded) < 1e-9)
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
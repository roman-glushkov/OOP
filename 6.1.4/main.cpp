#include <iostream>
#include <stdexcept>
#include "Solve3.h"

int main()
{
    double a, b, c, d;
    
    while (std::cin >> a >> b >> c >> d)
    {
        try
        {
            EquationRoots3 res = Solve3(a, b, c, d);
            
            std::cout << res.numRoots;
            for (int i = Config::ZERO; i < res.numRoots; i++)
            {
                std::cout << Config::SPACE << res.roots[i];
            }
            std::cout << std::endl;
        }
        catch (const std::invalid_argument& ex)
        {
            std::cout << Config::ERROR_PREFIX << ex.what() << std::endl;
        }
    }
    
    return Config::ZERO;
}
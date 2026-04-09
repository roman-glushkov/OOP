#include <iostream>
#include <iterator>
#include <algorithm> 
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
            
            std::copy(res.roots, res.roots + res.numRoots,std::ostream_iterator<double>(std::cout, " "));
            std::cout << std::endl;
        }
        catch (const std::invalid_argument& ex)
        {
            std::cout << Config::ERROR_PREFIX << ex.what() << std::endl;
        }
    }
    
    return Config::ZERO;
}
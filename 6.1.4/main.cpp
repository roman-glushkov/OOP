#include <iostream>
#include <stdexcept>

struct EquationRoots3
{
    int numRoots;
    double roots[3];
};

EquationRoots3 Solve3(double a, double b, double c, double d);

int main()
{
    double a, b, c, d;
    
    while (std::cin >> a >> b >> c >> d)
    {
        try
        {
            EquationRoots3 res = Solve3(a, b, c, d);
            
            std::cout << res.numRoots;
            for (int i = 0; i < res.numRoots; i++)
            {
                std::cout << " " << res.roots[i];
            }
            std::cout << std::endl;
        }
        catch (const std::invalid_argument& ex)
        {
            std::cout << "Error: " << ex.what() << std::endl;
        }
    }
    
    return 0;
}
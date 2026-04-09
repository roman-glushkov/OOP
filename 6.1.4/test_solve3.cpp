#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"
#include "Solve3.h" 
#include <cmath>
#include <stdexcept>

TEST_CASE("Invalid input")
{
    SECTION("a = 0")
    {
        CHECK_THROWS_AS(Solve3(0, 1, 1, 1), std::invalid_argument);
        CHECK_THROWS_AS(Solve3(0, 0, 0, 5), std::invalid_argument);
        CHECK_THROWS_AS(Solve3(0, 2, -3, 1), std::invalid_argument);
        CHECK_THROWS_AS(Solve3(0, 0, 0, 0), std::invalid_argument);
    }
    
    SECTION("a is very small but non-zero")
    {
        CHECK_NOTHROW(Solve3(1e-13, 1, 1, 1));
    }
}

TEST_CASE("Three real roots")
{
    SECTION("x^3 - 6x^2 + 11x - 6 = 0")
    {
        EquationRoots3 result = Solve3(1, -6, 11, -6);
        
        CHECK(result.numRoots == 3);
        CHECK(result.roots[0] == Approx(1.0));
        CHECK(result.roots[1] == Approx(2.0));
        CHECK(result.roots[2] == Approx(3.0));
    }
    
    SECTION("x^3 - 7x + 6 = 0")
    {
        EquationRoots3 result = Solve3(1, 0, -7, 6);
        
        CHECK(result.numRoots == 3);
        CHECK(result.roots[0] == Approx(-3.0));
        CHECK(result.roots[1] == Approx(1.0));
        CHECK(result.roots[2] == Approx(2.0));
    }
    
    SECTION("x^3 - 2x^2 - 5x + 6 = 0")
    {
        EquationRoots3 result = Solve3(1, -2, -5, 6);
        
        CHECK(result.numRoots == 3);
        CHECK(result.roots[0] == Approx(-2.0));
        CHECK(result.roots[1] == Approx(1.0));
        CHECK(result.roots[2] == Approx(3.0));
    }
    
    SECTION("-x^3 + 6x^2 - 11x + 6 = 0")
    {
        EquationRoots3 result = Solve3(-1, 6, -11, 6);
        
        CHECK(result.numRoots == 3);
        CHECK(result.roots[0] == Approx(1.0));
        CHECK(result.roots[1] == Approx(2.0));
        CHECK(result.roots[2] == Approx(3.0));
    }
    
    SECTION("x^3 - 3x = 0")
    {
        EquationRoots3 result = Solve3(1, 0, -3, 0);
        
        CHECK(result.numRoots == 3);
        CHECK(result.roots[0] == Approx(-1.73205080757));
        CHECK(result.roots[1] == Approx(0.0));
        CHECK(result.roots[2] == Approx(1.73205080757));
    }
}

TEST_CASE("Multiple roots")
{
    SECTION("(x-1)^2 (x-2) = 0")
    {
        EquationRoots3 result = Solve3(1, -4, 5, -2);
        
        CHECK(result.numRoots == 2);
        CHECK(result.roots[0] == Approx(1.0));
        CHECK(result.roots[1] == Approx(2.0));
    }
    
    SECTION("(x+1)^2 (x-2) = 0")
    {
        EquationRoots3 result = Solve3(1, 0, -3, -2);
        
        CHECK(result.numRoots == 2);
        CHECK(result.roots[0] == Approx(-1.0));
        CHECK(result.roots[1] == Approx(2.0));
    }
    
    SECTION("(x-1)^3 = 0")
    {
        EquationRoots3 result = Solve3(1, -3, 3, -1);
        
        CHECK(result.numRoots == 1);
        CHECK(result.roots[0] == Approx(1.0));
    }
    
    SECTION("x^3 = 0")
    {
        EquationRoots3 result = Solve3(1, 0, 0, 0);
        
        CHECK(result.numRoots == 1);
        CHECK(result.roots[0] == Approx(0.0));
    }
    
    SECTION("x^3 + x^2 = 0")
    {
        EquationRoots3 result = Solve3(1, 1, 0, 0);
        
        CHECK(result.numRoots == 2);
        CHECK(result.roots[0] == Approx(-1.0));
        CHECK(result.roots[1] == Approx(0.0));
    }
}

TEST_CASE("One real root")
{
    SECTION("x^3 - 3x^2 + 4x - 2 = 0")
    {
        EquationRoots3 result = Solve3(1, -3, 4, -2);
        
        CHECK(result.numRoots == 1);
        CHECK(result.roots[0] == Approx(1.0));
    }
    
    SECTION("x^3 + x + 1 = 0")
    {
        EquationRoots3 result = Solve3(1, 0, 1, 1);
        
        CHECK(result.numRoots == 1);
    }
    
    SECTION("x^3 + 2x = 0")
    {
        EquationRoots3 result = Solve3(1, 0, 2, 0);
        
        CHECK(result.numRoots == 1);
        CHECK(result.roots[0] == Approx(0.0));
    }
    
    SECTION("x^3 + x^2 + x = 0")
    {
        EquationRoots3 result = Solve3(1, 1, 1, 0);
        
        CHECK(result.numRoots == 1);
        CHECK(result.roots[0] == Approx(0.0));
    }
}

TEST_CASE("Large and small coefficients")
{
    SECTION("Large coefficients")
    {
        EquationRoots3 result = Solve3(1e10, -6e10, 11e10, -6e10);
        
        CHECK(result.numRoots == 3);
        CHECK(result.roots[0] == Approx(1.0));
        CHECK(result.roots[1] == Approx(2.0));
        CHECK(result.roots[2] == Approx(3.0));
    }
    
    SECTION("Small coefficients")
    {
        EquationRoots3 result = Solve3(1e-10, -6e-10, 11e-10, -6e-10);
        
        CHECK(result.numRoots == 3);
        CHECK(result.roots[0] == Approx(1.0).epsilon(1e-5));
        CHECK(result.roots[1] == Approx(2.0).epsilon(1e-5));
        CHECK(result.roots[2] == Approx(3.0).epsilon(1e-5));
    }
}

TEST_CASE("Sorting and duplicates")
{
    SECTION("Roots are sorted")
    {
        EquationRoots3 result = Solve3(1, -6, 11, -6);
        
        CHECK(result.roots[0] < result.roots[1]);
        CHECK(result.roots[1] < result.roots[2]);
    }
    
    SECTION("Near-duplicate roots are merged")
    {
        EquationRoots3 result = Solve3(1, -4.000000001, 5.000000002, -2.000000001);
        
        CHECK(result.numRoots == 2);
    }
}
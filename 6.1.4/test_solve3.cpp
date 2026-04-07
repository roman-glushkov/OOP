#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"
#include "Solve3.h" 
#include <cmath>
#include <stdexcept>

TEST_CASE("Solve3 handles invalid input")
{
    SECTION("Zero coefficient at x^3 throws exception")
    {
        CHECK_THROWS_AS(Solve3(0, 1, 1, 1), std::invalid_argument);
        CHECK_THROWS_AS(Solve3(0, 0, 0, 5), std::invalid_argument);
        CHECK_THROWS_AS(Solve3(0, 2, -3, 1), std::invalid_argument);
    }
    
    SECTION("Exception message is correct")
    {
        try 
        {
            Solve3(0, 1, 1, 1);
            FAIL("Expected exception not thrown");
        }
        catch (const std::invalid_argument& ex)
        {
            std::string msg = ex.what();
            CHECK(msg.find("x^3") != std::string::npos);
            CHECK(msg.find("zero") != std::string::npos);
        }
    }
    
    SECTION("Very small but non-zero coefficient is acceptable")
    {
        CHECK_NOTHROW(Solve3(1e-13, 1, 1, 1));
    }
}

TEST_CASE("Solve3 cubic equations with three real roots")
{
    SECTION("Simple cubic: x^3 - 6x^2 + 11x - 6 = 0, roots: 1, 2, 3")
    {
        EquationRoots3 result = Solve3(1, -6, 11, -6);
        
        CHECK(result.numRoots == 3);
        CHECK(result.roots[0] == Approx(1.0));
        CHECK(result.roots[1] == Approx(2.0));
        CHECK(result.roots[2] == Approx(3.0));
    }
    
    SECTION("x^3 - 7x + 6 = 0, roots: -3, 1, 2")
    {
        EquationRoots3 result = Solve3(1, 0, -7, 6);
        
        CHECK(result.numRoots == 3);
        CHECK(result.roots[0] == Approx(-3.0));
        CHECK(result.roots[1] == Approx(1.0));
        CHECK(result.roots[2] == Approx(2.0));
    }
    
    SECTION("x^3 - 2x^2 - 5x + 6 = 0, roots: -2, 1, 3")
    {
        EquationRoots3 result = Solve3(1, -2, -5, 6);
        
        CHECK(result.numRoots == 3);
        CHECK(result.roots[0] == Approx(-2.0));
        CHECK(result.roots[1] == Approx(1.0));
        CHECK(result.roots[2] == Approx(3.0));
    }
    
    SECTION("Negative coefficients: -x^3 + 6x^2 - 11x + 6 = 0, roots: 1, 2, 3")
    {
        EquationRoots3 result = Solve3(-1, 6, -11, 6);
        
        CHECK(result.numRoots == 3);
        CHECK(result.roots[0] == Approx(1.0));
        CHECK(result.roots[1] == Approx(2.0));
        CHECK(result.roots[2] == Approx(3.0));
    }
}

TEST_CASE("Solve3 equations with multiple/double roots")
{
    SECTION("Double root: (x-1)^2*(x-2) = x^3 - 4x^2 + 5x - 2 = 0")
    {
        EquationRoots3 result = Solve3(1, -4, 5, -2);
        
        CHECK(result.numRoots == 2);
        CHECK(result.roots[0] == Approx(1.0));
        CHECK(result.roots[1] == Approx(2.0));
    }
    
    SECTION("Double root negative: (x+1)^2*(x-2) = x^3 - 3x - 2 = 0")
    {
        EquationRoots3 result = Solve3(1, 0, -3, -2);
        
        CHECK(result.numRoots == 2);
        CHECK(result.roots[0] == Approx(-1.0));
        CHECK(result.roots[1] == Approx(2.0));
    }
    
    SECTION("Triple root: (x-1)^3 = x^3 - 3x^2 + 3x - 1 = 0")
    {
        EquationRoots3 result = Solve3(1, -3, 3, -1);

        CHECK(result.numRoots == 1);
        CHECK(result.roots[0] == Approx(1.0));
    }
}

TEST_CASE("Solve3 equations with one real root")
{
    SECTION("x^3 + x^2 + x + 1 = 0, real root ≈ -0.5?")
    {
        EquationRoots3 result = Solve3(1, 1, 1, 1);
        
        CHECK(result.numRoots == 1);
        double x = result.roots[0];
        double value = x*x*x + x*x + x + 1;
        CHECK(fabs(value) < 1e-9);
    }
    
    SECTION("x^3 - 3x^2 + 4x - 2 = 0, real root = 1")
    {
        EquationRoots3 result = Solve3(1, -3, 4, -2);
        
        CHECK(result.numRoots == 1);
        CHECK(result.roots[0] == Approx(1.0));
    }
    
    SECTION("x^3 + 2x^2 + 3x + 4 = 0, one real root ≈ -1.6506")
    {
        EquationRoots3 result = Solve3(1, 2, 3, 4);
        
        CHECK(result.numRoots == 1);
        double x = result.roots[0];
        double value = x*x*x + 2*x*x + 3*x + 4;
        CHECK(fabs(value) < 1e-9);
    }
    
    SECTION("x^3 - 5x^2 + 8x - 6 = 0, one real root ≈ 3")
    {
        EquationRoots3 result = Solve3(1, -5, 8, -6);
        
        CHECK(result.numRoots == 1);
        double x = result.roots[0];
        CHECK(fabs(x - 3.0) < 0.1);
    }
}

TEST_CASE("Solve3 edge cases")
{
    SECTION("Very large coefficients")
    {
        EquationRoots3 result = Solve3(1e10, -6e10, 11e10, -6e10);
        CHECK(result.numRoots == 3);
        CHECK(result.roots[0] == Approx(1.0));
        CHECK(result.roots[1] == Approx(2.0));
        CHECK(result.roots[2] == Approx(3.0));
    }
    
    SECTION("Very small coefficients")
    {
        EquationRoots3 result = Solve3(1e-10, -6e-10, 11e-10, -6e-10);
        CHECK(result.numRoots == 3);
        CHECK(result.roots[0] == Approx(1.0).epsilon(1e-5));
        CHECK(result.roots[1] == Approx(2.0).epsilon(1e-5));
        CHECK(result.roots[2] == Approx(3.0).epsilon(1e-5));
    }
    
    SECTION("All coefficients zero except a - throws exception")
    {
        CHECK_THROWS_AS(Solve3(0, 0, 0, 0), std::invalid_argument);
    }
}

TEST_CASE("Solve3 special cubic forms")
{
    SECTION("Depressed cubic: x^3 + px + q = 0, three roots")
    {
        EquationRoots3 result = Solve3(1, 0, -7, 6);
        CHECK(result.numRoots == 3);
    }
    
    SECTION("Depressed cubic with one root: x^3 + x + 1 = 0")
    {
        EquationRoots3 result = Solve3(1, 0, 1, 1);
        CHECK(result.numRoots == 1);
    }
    
    SECTION("x^3 + 2x = 0, roots: 0, ±i√2 (only real: 0)")
    {
        EquationRoots3 result = Solve3(1, 0, 2, 0);
        CHECK(result.numRoots == 1);
        CHECK(result.roots[0] == Approx(0.0));
    }
    
    SECTION("x^3 - 3x = 0, roots: -√3, 0, √3")
    {
        EquationRoots3 result = Solve3(1, 0, -3, 0);
        CHECK(result.numRoots == 3);
        CHECK(result.roots[0] == Approx(-1.73205080757));
        CHECK(result.roots[1] == Approx(0.0));
        CHECK(result.roots[2] == Approx(1.73205080757));
    }
}

TEST_CASE("Solve3 sorting and duplicate removal")
{
    SECTION("Roots should be sorted in ascending order")
    {
        EquationRoots3 result = Solve3(1, -6, 11, -6);
        CHECK(result.roots[0] < result.roots[1]);
        CHECK(result.roots[1] < result.roots[2]);
    }
    
    SECTION("Duplicate roots should be removed")
    {
        EquationRoots3 result = Solve3(1, -4, 5, -2);
        CHECK(result.numRoots == 2);
        CHECK(result.roots[0] != result.roots[1]);
    }
    
    SECTION("Near-duplicate roots within tolerance")
    {
        EquationRoots3 result = Solve3(1, -4.000000001, 5.000000002, -2.000000001);
        CHECK(result.numRoots == 2);
    }
}
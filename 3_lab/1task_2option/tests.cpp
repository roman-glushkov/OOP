#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "functions.h"
#include <sstream>

TEST_CASE("ReadNumbers reads valid input")
{
    std::istringstream input("1.5 2.5 3.5");
    bool isValid = true;

    auto result = ReadNumbers(input, isValid);

    REQUIRE(isValid);
    REQUIRE(result.size() == 3);
    CHECK(result[0] == Approx(1.5));
    CHECK(result[1] == Approx(2.5));
    CHECK(result[2] == Approx(3.5));
}

TEST_CASE("ReadNumbers detects invalid input")
{
    std::istringstream input("1.5 abc");
    bool isValid = true;

    auto result = ReadNumbers(input, isValid);

    CHECK_FALSE(isValid);
}

TEST_CASE("ProcessNumbers multiplies by minimum")
{
    std::vector<double> input{2.0, 4.0, -1.5};
    auto result = ProcessNumbers(input);

    std::vector<double> expected{-3.0, -6.0, 2.25};
    CHECK(result == expected);
} // тсты на мин 0, макс инт, мин инт

TEST_CASE("ProcessNumbers with all positive and minimum zero")
{
    std::vector<double> input{5.0, 3.0, 0.0, 7.0};
    auto result = ProcessNumbers(input);

    std::vector<double> expected{0.0, 0.0, 0.0, 0.0};
    CHECK(result == expected);
}

TEST_CASE("ProcessNumbers with maximum integer values")
{
    double maxInt = INT_MAX;
    std::vector<double> input{maxInt, 5.0, -2.0};
    auto result = ProcessNumbers(input);

    std::vector<double> expected{-2.0 * maxInt, -10.0, 4.0};
    CHECK(result == expected);
}

TEST_CASE("ProcessNumbers with minimum integer values")
{
    double minInt = INT_MIN;
    std::vector<double> input{minInt, 5.0, -2.0};
    auto result = ProcessNumbers(input);

    std::vector<double> expected{minInt * minInt, 5.0 * minInt, -2.0 * minInt};
    CHECK(result == expected);
}

TEST_CASE("ProcessNumbers handles empty vector")
{
    std::vector<double> input;
    auto result = ProcessNumbers(input);

    CHECK(result.empty());
}

TEST_CASE("PrintSortedNumbers prints sorted output")
{
    std::vector<double> input{3.0, 1.0, 2.0};
    std::ostringstream output;

    PrintSortedNumbers(input, output);

    CHECK(output.str() == "1.000 2.000 3.000\n");
} // 0, -

TEST_CASE("PrintSortedNumbers with negative values")
{
    std::vector<double> input{-5.0, -1.0, -10.0};
    std::ostringstream output;

    PrintSortedNumbers(input, output);

    CHECK(output.str() == "-10.000 -5.000 -1.000\n");
}

TEST_CASE("PrintSortedNumbers with three zeros")
{
    std::vector<double> input{0.0, 0.0, 0.0};
    std::ostringstream output;

    PrintSortedNumbers(input, output);

    CHECK(output.str() == "0.000 0.000 0.000\n");
}
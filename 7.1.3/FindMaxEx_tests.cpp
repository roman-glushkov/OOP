#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"
#include "FindMaxEx.h"
#include "Controller.h"
#include "Config.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>

struct TestAthlete
{
    std::string name;
    double height;
    double weight;
};

TEST_CASE("Empty array")
{
    std::vector<int> arr;
    int maxValue = 42;

    bool result = FindMaxEx(arr, maxValue, [](int a, int b) { return a < b; });

    CHECK(result == false);
    CHECK(maxValue == 42);
}

TEST_CASE("Single element")
{
    std::vector<int> arr = {100};
    int maxValue = 0;

    bool result = FindMaxEx(arr, maxValue, [](int a, int b) { return a < b; });

    CHECK(result == true);
    CHECK(maxValue == 100);
}

TEST_CASE("Integers")
{
    SECTION("General case")
    {
        std::vector<int> arr = {5, -2, 8, 1, 9, -3};
        int maxValue = 0;

        bool result = FindMaxEx(arr, maxValue, [](int a, int b) { return a < b; });

        CHECK(result == true);
        CHECK(maxValue == 9);
    }

    SECTION("All equal")
    {
        std::vector<int> arr = {7, 7, 7, 7};
        int maxValue = 0;

        bool result = FindMaxEx(arr, maxValue, [](int a, int b) { return a < b; });

        CHECK(result == true);
        CHECK(maxValue == 7);
    }

    SECTION("Sorted ascending")
    {
        std::vector<int> arr = {1, 2, 3, 4, 5};
        int maxValue = 0;

        bool result = FindMaxEx(arr, maxValue, [](int a, int b) { return a < b; });

        CHECK(result == true);
        CHECK(maxValue == 5);
    }

    SECTION("Sorted descending")
    {
        std::vector<int> arr = {5, 4, 3, 2, 1};
        int maxValue = 0;

        bool result = FindMaxEx(arr, maxValue, [](int a, int b) { return a < b; });

        CHECK(result == true);
        CHECK(maxValue == 5);
    }
}

TEST_CASE("Doubles")
{
    std::vector<double> arr = {1.5, 3.7, 2.1, 5.9, 4.2};
    double maxValue = 0.0;

    bool result = FindMaxEx(arr, maxValue, [](double a, double b) { return a < b; });

    CHECK(result == true);
    CHECK(maxValue == Approx(5.9));
}

TEST_CASE("Strings")
{
    std::vector<std::string> arr = {"apple", "banana", "pear", "grape"};
    std::string maxValue;

    bool result = FindMaxEx(arr, maxValue, [](const std::string& a, const std::string& b)
    {
        return a < b;
    });

    CHECK(result == true);
    CHECK(maxValue == "pear");
}

TEST_CASE("Reverse comparator")
{
    std::vector<int> arr = {10, 20, 5, 30, 15};
    int minValue = 0;

    bool result = FindMaxEx(arr, minValue, [](int a, int b)
    {
        return a > b;
    });

    CHECK(result == true);
    CHECK(minValue == 5);
}

TEST_CASE("Athlete by height")
{
    std::vector<TestAthlete> arr =
    {
        {"Ivanov", 1.85, 80.5},
        {"Petrov", 1.92, 95.0},
        {"Sidorov", 1.68, 58.7}
    };

    TestAthlete result;

    bool found = FindMaxEx(arr, result, [](const TestAthlete& a, const TestAthlete& b)
    {
        return a.height < b.height;
    });

    CHECK(found == true);
    CHECK(result.name == "Petrov");
    CHECK(result.height == Approx(1.92));
}

TEST_CASE("Athlete by weight")
{
    std::vector<TestAthlete> arr =
    {
        {"Ivanov", 1.85, 80.5},
        {"Petrov", 1.92, 95.0},
        {"Sidorov", 1.68, 58.7}
    };

    TestAthlete result;

    bool found = FindMaxEx(arr, result, [](const TestAthlete& a, const TestAthlete& b)
    {
        return a.weight < b.weight;
    });

    CHECK(found == true);
    CHECK(result.name == "Petrov");
    CHECK(result.weight == Approx(95.0));
}

TEST_CASE("Strong exception guarantee")
{
    struct ThrowOnAssign
    {
        int value;
        ThrowOnAssign(int v = 0) : value(v) {}
        ThrowOnAssign& operator=(const ThrowOnAssign&)
        {
            throw std::runtime_error("assignment failed");
        }
    };

    std::vector<ThrowOnAssign> arr = {1, 2, 3};
    ThrowOnAssign maxValue(999);

    CHECK_THROWS_AS(
        FindMaxEx(arr, maxValue, [](const ThrowOnAssign& a, const ThrowOnAssign& b)
        {
            return a.value < b.value;
        }),
        std::runtime_error
    );

    CHECK(maxValue.value == 999);
}

TEST_CASE("Controller")
{
    SECTION("Valid file")
    {
        std::ofstream file(Config::DATABASE_FILE);
        file << "Ivanov|1.85|80.5\n";
        file << "Petrov|1.92|95.0\n";
        file << "Sidorov|1.68|58.7\n";
        file.close();

        std::ostringstream output;
        std::streambuf* old = std::cout.rdbuf(output.rdbuf());

        Controller::ProcessCommands();

        std::cout.rdbuf(old);

        std::string result = output.str();

        CHECK(result.find(Config::MSG_SEARCH_HEIGHT) != std::string::npos);
        CHECK(result.find(Config::MSG_SEARCH_WEIGHT) != std::string::npos);
        CHECK(result.find("Petrov") != std::string::npos);
    }

    SECTION("Invalid data validation")
    {
        std::ofstream file(Config::DATABASE_FILE);
        file << "Invalid1|-1.5|50\n";
        file << "Invalid2|1.8|-10\n";
        file << "Valid|1.9|90\n";
        file.close();

        std::ostringstream output;
        std::streambuf* old = std::cout.rdbuf(output.rdbuf());

        Controller::ProcessCommands();

        std::cout.rdbuf(old);

        std::string result = output.str();

        CHECK(result.find(Config::ERROR_HEIGHT_POSITIVE) != std::string::npos);
        CHECK(result.find(Config::ERROR_WEIGHT_POSITIVE) != std::string::npos);
        CHECK(result.find("Valid") != std::string::npos);
    }

    SECTION("File not found")
    {
        std::remove(Config::DATABASE_FILE);

        std::ostringstream output;
        std::streambuf* old = std::cout.rdbuf(output.rdbuf());

        Controller::ProcessCommands();

        std::cout.rdbuf(old);

        CHECK(output.str().find(Config::ERROR_FILE_NOT_OPEN) != std::string::npos);
    }

    SECTION("Empty file")
    {
        std::ofstream file(Config::DATABASE_FILE);
        file.close();

        std::ostringstream output;
        std::streambuf* old = std::cout.rdbuf(output.rdbuf());

        Controller::ProcessCommands();

        std::cout.rdbuf(old);

        CHECK(output.str().find(Config::ERROR_EMPTY_ARRAY) != std::string::npos);
    }
}
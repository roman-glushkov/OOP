#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"

#include "FindMaxEx.h"
#include "Controller.h"
#include "Config.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

// -------------------- BASIC TYPES --------------------

TEST_CASE("FindMaxEx with integers")
{
    std::vector<int> arr = {1, 5, 3, 9, 2};
    int maxValue = 0;

    bool result = FindMaxEx(arr, maxValue, [](int a, int b)
    {
        return a < b;
    });

    CHECK(result == true);
    CHECK(maxValue == 9);
}

TEST_CASE("FindMaxEx with doubles")
{
    std::vector<double> arr = {1.1, 5.5, 3.3};
    double maxValue = 0;

    bool result = FindMaxEx(arr, maxValue, [](double a, double b)
    {
        return a < b;
    });

    CHECK(result == true);
    CHECK(maxValue == Approx(5.5));
}

// -------------------- STRINGS --------------------

TEST_CASE("FindMaxEx with strings (lexicographical)")
{
    std::vector<std::string> arr = {"apple", "banana", "pear"};
    std::string maxValue;

    bool result = FindMaxEx(arr, maxValue, [](const std::string& a, const std::string& b)
    {
        return a < b;
    });

    CHECK(result == true);
    CHECK(maxValue == "pear");
}

// -------------------- EDGE CASES --------------------

TEST_CASE("Empty array")
{
    std::vector<int> arr;
    int maxValue = 42;

    bool result = FindMaxEx(arr, maxValue, [](int a, int b)
    {
        return a < b;
    });

    CHECK(result == false);
    CHECK(maxValue == 42); // commit-or-rollback
}

TEST_CASE("Single element")
{
    std::vector<int> arr = {7};
    int maxValue = 0;

    bool result = FindMaxEx(arr, maxValue, [](int a, int b)
    {
        return a < b;
    });

    CHECK(result == true);
    CHECK(maxValue == 7);
}

TEST_CASE("All elements equal")
{
    std::vector<int> arr = {5, 5, 5, 5};
    int maxValue = 0;

    bool result = FindMaxEx(arr, maxValue, [](int a, int b)
    {
        return a < b;
    });

    CHECK(result == true);
    CHECK(maxValue == 5);
}

// -------------------- CUSTOM COMPARATORS --------------------

TEST_CASE("Find minimum using reversed comparator")
{
    std::vector<int> arr = {10, 20, 5, 30};
    int value = 0;

    bool result = FindMaxEx(arr, value, [](int a, int b)
    {
        return a > b; // reverse logic
    });

    CHECK(result == true);
    CHECK(value == 5);
}

// -------------------- CUSTOM TYPE --------------------

struct Athlete
{
    std::string name;
    double height;
    double weight;
};

TEST_CASE("FindMaxEx with Athlete by height")
{
    std::vector<Athlete> arr =
    {
        {"A", 1.7, 60},
        {"B", 1.9, 80},
        {"C", 1.8, 70}
    };

    Athlete result;

    bool found = FindMaxEx(arr, result, [](const Athlete& a, const Athlete& b)
    {
        return a.height < b.height;
    });

    CHECK(found == true);
    CHECK(result.name == "B");
}

TEST_CASE("FindMaxEx with Athlete by weight")
{
    std::vector<Athlete> arr =
    {
        {"A", 1.7, 60},
        {"B", 1.9, 80},
        {"C", 1.8, 90}
    };

    Athlete result;

    bool found = FindMaxEx(arr, result, [](const Athlete& a, const Athlete& b)
    {
        return a.weight < b.weight;
    });

    CHECK(found == true);
    CHECK(result.name == "C");
}

// -------------------- EXCEPTION SAFETY --------------------

struct ThrowOnAssign
{
    int value;

    ThrowOnAssign(int v = 0) : value(v) {}

    ThrowOnAssign& operator=(const ThrowOnAssign&)
    {
        throw std::runtime_error("Assignment failed");
    }
};

TEST_CASE("Strong exception guarantee (commit-or-rollback)")
{
    std::vector<ThrowOnAssign> arr = {1, 2, 3};
    ThrowOnAssign maxValue(999);

    CHECK_THROWS_AS(
        FindMaxEx(arr, maxValue, [](const ThrowOnAssign& a, const ThrowOnAssign& b)
        {
            return a.value < b.value;
        }),
        std::runtime_error
    );

    CHECK(maxValue.value == 999); // не изменился
}

// -------------------- CONTROLLER TESTS --------------------

TEST_CASE("Controller full process - valid file")
{
    // создаём тестовый файл
    std::ofstream file(Config::DATABASE_FILE);
    file << "A|1.5|50\n";
    file << "B|2.0|80\n";
    file << "C|1.8|90\n";
    file.close();

    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    Controller::ProcessCommands();

    std::cout.rdbuf(oldCout);

    std::string result = output.str();

    CHECK(result.find("Searching athlete with maximum height") != std::string::npos);
    CHECK(result.find("Searching athlete with maximum weight") != std::string::npos);
    CHECK(result.find("B") != std::string::npos); // tallest
    CHECK(result.find("C") != std::string::npos); // heaviest
}

TEST_CASE("Controller - empty file")
{
    std::ofstream file(Config::DATABASE_FILE);
    file.close();

    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    Controller::ProcessCommands();

    std::cout.rdbuf(oldCout);

    CHECK(output.str().find(Config::ERROR_EMPTY_ARRAY) != std::string::npos);
}

TEST_CASE("Controller - file not found")
{
    std::remove(Config::DATABASE_FILE);

    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    Controller::ProcessCommands();

    std::cout.rdbuf(oldCout);

    std::string result = output.str();

    CHECK(result.find(Config::ERROR_FILE_NOT_OPEN) != std::string::npos);
}
#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"
#include "FindMaxEx.h"
#include "Controller.h"
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

struct TestAthlete
{
    std::string name;
    double height;
    double weight;
};


TEST_CASE("FindMaxEx - empty array returns false")
{
    std::vector<int> arr;
    int maxValue = 42;

    bool result = FindMaxEx(arr, maxValue, [](int a, int b) { return a < b; });

    CHECK(result == false);
    CHECK(maxValue == 42); 
}

TEST_CASE("FindMaxEx - single element")
{
    std::vector<int> arr = {100};
    int maxValue = 0;

    bool result = FindMaxEx(arr, maxValue, [](int a, int b) { return a < b; });

    CHECK(result == true);
    CHECK(maxValue == 100);
}

TEST_CASE("FindMaxEx - integers")
{
    std::vector<int> arr = {5, -2, 8, 1, 9, -3};
    int maxValue = 0;

    bool result = FindMaxEx(arr, maxValue, [](int a, int b) { return a < b; });

    CHECK(result == true);
    CHECK(maxValue == 9);
}

TEST_CASE("FindMaxEx - all equal integers")
{
    std::vector<int> arr = {7, 7, 7, 7};
    int maxValue = 0;

    bool result = FindMaxEx(arr, maxValue, [](int a, int b) { return a < b; });

    CHECK(result == true);
    CHECK(maxValue == 7);
}

TEST_CASE("FindMaxEx - doubles")
{
    std::vector<double> arr = {1.5, 3.7, 2.1, 5.9, 4.2};
    double maxValue = 0.0;

    bool result = FindMaxEx(arr, maxValue, [](double a, double b) { return a < b; });

    CHECK(result == true);
    CHECK(maxValue == Approx(5.9));
}

TEST_CASE("FindMaxEx - strings")
{
    std::vector<std::string> arr = {"apple", "banana", "pear", "grape"};
    std::string maxValue;

    bool result = FindMaxEx(arr, maxValue, [](const std::string& a, const std::string& b) {
        return a < b;
    });

    CHECK(result == true);
    CHECK(maxValue == "pear");
}

TEST_CASE("FindMaxEx - TestAthlete by height")
{
    std::vector<TestAthlete> arr = {
        {"Ivanov", 1.85, 80.5},
        {"Petrov", 1.92, 95.0},
        {"Sidorov", 1.68, 58.7}
    };

    TestAthlete result;

    bool found = FindMaxEx(arr, result, [](const TestAthlete& a, const TestAthlete& b) {
        return a.height < b.height;
    });

    CHECK(found == true);
    CHECK(result.name == "Petrov");
    CHECK(result.height == Approx(1.92));
}

TEST_CASE("FindMaxEx - TestAthlete by weight")
{
    std::vector<TestAthlete> arr = {
        {"Ivanov", 1.85, 80.5},
        {"Petrov", 1.92, 95.0},
        {"Sidorov", 1.68, 58.7}
    };

    TestAthlete result;

    bool found = FindMaxEx(arr, result, [](const TestAthlete& a, const TestAthlete& b) {
        return a.weight < b.weight;
    });

    CHECK(found == true);
    CHECK(result.name == "Petrov");
    CHECK(result.weight == Approx(95.0));
}

TEST_CASE("Controller - normal case with 3 athletes")
{
    std::vector<Athlete> athletes = {
        {"Ivanov", 1.85, 80.5},
        {"Petrov", 1.92, 95.0},
        {"Sidorov", 1.68, 58.7}
    };
    
    std::string result = Controller::ProcessCommands(athletes);

    CHECK(result.find("Petrov") != std::string::npos);
    CHECK(result.find("1.92") != std::string::npos);
    CHECK(result.find("95") != std::string::npos);
}

TEST_CASE("Controller - empty array")
{
    std::vector<Athlete> empty;
    
    std::string result = Controller::ProcessCommands(empty);
    
    std::string expected = "Error: array is empty\n";
    
    CHECK(result == expected);
}

TEST_CASE("Controller - single athlete")
{
    std::vector<Athlete> athletes = {
        {"OnlyOne", 1.75, 70.0}
    };
    
    std::string result = Controller::ProcessCommands(athletes);
    
    std::string expected = 
        "Searching athlete with maximum height...\n"
        "OnlyOne | 1.75 m | 70 kg\n"
        "\n"
        "Searching athlete with maximum weight...\n"
        "OnlyOne | 1.75 m | 70 kg\n";
    
    CHECK(result == expected);
}

TEST_CASE("Controller - athletes with same height different weight")
{
    std::vector<Athlete> athletes = {
        {"First", 1.90, 80.0},
        {"Second", 1.90, 85.0},
        {"Third", 1.80, 75.0}
    };
    
    std::string result = Controller::ProcessCommands(athletes);
    
    std::string expected = 
        "Searching athlete with maximum height...\n"
        "First | 1.9 m | 80 kg\n"
        "\n"
        "Searching athlete with maximum weight...\n"
        "Second | 1.9 m | 85 kg\n";
    
    CHECK(result == expected);
}

TEST_CASE("Controller - athletes with same weight different height")
{
    std::vector<Athlete> athletes = {
        {"Tall", 1.95, 80.0},
        {"Short", 1.65, 80.0},
        {"Middle", 1.80, 75.0}
    };
    
    std::string result = Controller::ProcessCommands(athletes);
    
    std::string expected = 
        "Searching athlete with maximum height...\n"
        "Tall | 1.95 m | 80 kg\n"
        "\n"
        "Searching athlete with maximum weight...\n"
        "Tall | 1.95 m | 80 kg\n";
    
    CHECK(result == expected);
}

TEST_CASE("Controller - two separate searches different athletes")
{
    std::vector<Athlete> athletes = {
        {"TallLight", 2.00, 70.0},
        {"ShortHeavy", 1.60, 100.0},
        {"Average", 1.80, 80.0}
    };
    
    std::string result = Controller::ProcessCommands(athletes);
    
    std::string expected = 
        "Searching athlete with maximum height...\n"
        "TallLight | 2 m | 70 kg\n"
        "\n"
        "Searching athlete with maximum weight...\n"
        "ShortHeavy | 1.6 m | 100 kg\n";
    
    CHECK(result == expected);
}

TEST_CASE("Controller - negative values are validated")
{
    CHECK_THROWS_AS(Athlete("Bad", -1.0, 70.0), std::invalid_argument);
    CHECK_THROWS_AS(Athlete("Bad", 1.80, -10.0), std::invalid_argument);
    CHECK_NOTHROW(Athlete("Good", 1.80, 70.0));
}
#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"
#include "CDate.h"
#include <sstream>

TEST_CASE("CDate can be created from day-month-year and all getters work", "[getters]")
{
    // Создаём дату 25.12.2020
    CDate date(25, Month::DECEMBER, 2020);
    
    // Проверяем, что дата валидна
    REQUIRE(date.IsValid() == true);
    
    // Проверяем все геттеры
    CHECK(date.GetDay() == 25);
    CHECK(static_cast<int>(date.GetMonth()) == 12);
    CHECK(date.GetYear() == 2020);
    
    // Проверяем день недели (25.12.2020 была пятница = 5)
    CHECK(static_cast<int>(date.GetWeekDay()) == 5);
    
    // Проверяем вывод через оператор <<
    std::ostringstream oss;
    oss << date;
    CHECK(oss.str() == "25.12.2020");
}

TEST_CASE("CDate operator+ adds days correctly", "[operator+]")
{
    // Тест: 28.02.2010 + 3 = 03.03.2010
    CDate date(28, Month::FEBRUARY, 2010);
    CDate result = date + 3;
    
    // Проверяем результат
    CHECK(result.GetDay() == 3);
    CHECK(static_cast<int>(result.GetMonth()) == 3); // March
    CHECK(result.GetYear() == 2010);
    
    // Проверяем, что исходная дата не изменилась
    CHECK(date.GetDay() == 28);
    CHECK(static_cast<int>(date.GetMonth()) == 2);
    
    // Проверяем через оператор <<
    std::ostringstream oss;
    oss << result;
    CHECK(oss.str() == "03.03.2010");
}
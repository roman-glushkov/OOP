#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"
#include "CDate.h"
#include "CDateController.h"
#include <sstream>
#include <string>

TEST_CASE("CDate basic functionality")
{
    SECTION("Default constructor")
    {
        CDate date;
        CHECK(date.GetDay() == 1);
        CHECK(date.GetMonth() == Month::JANUARY);
        CHECK(date.GetYear() == 1970);
        CHECK(date.GetWeekDay() == WeekDay::THURSDAY);
        CHECK(date.IsValid());
    }

    SECTION("Valid date creation")
    {
        CDate date(23, Month::MARCH, 2010);
        CHECK(date.GetDay() == 23);
        CHECK(date.GetMonth() == Month::MARCH);
        CHECK(date.GetYear() == 2010);
        CHECK(date.IsValid());
    }

    SECTION("Timestamp constructor")
    {
        CDate date(32);
        CHECK(date.GetDay() == 2);
        CHECK(date.GetMonth() == Month::FEBRUARY);
        CHECK(date.GetYear() == 1970);
        CHECK(date.IsValid());
    }

    SECTION("Invalid dates")
    {
        CHECK_FALSE(CDate(0, Month::JANUARY, 1970).IsValid());
        CHECK_FALSE(CDate(31, Month::FEBRUARY, 2020).IsValid());
        CHECK_FALSE(CDate(1, Month::JANUARY, 1969).IsValid());
        CHECK_FALSE(CDate(1, Month::JANUARY, 10000).IsValid());
        CHECK_FALSE(CDate(-1).IsValid());
        CHECK_FALSE(CDate(9999999).IsValid());
    }
}

TEST_CASE("Getters and weekday")
{
    SECTION("Leap year date")
    {
        CDate date(29, Month::FEBRUARY, 2020);
        CHECK(date.GetWeekDay() == WeekDay::SATURDAY);
    }

    SECTION("End of year")
    {
        CDate date(31, Month::DECEMBER, 2023);
        CHECK(date.GetWeekDay() == WeekDay::SUNDAY);
    }

    SECTION("Beginning of year")
    {
        CDate date(1, Month::JANUARY, 2024);
        CHECK(date.GetWeekDay() == WeekDay::MONDAY);
    }
}

TEST_CASE("Operators")
{
    SECTION("Increment / Decrement")
    {
        CDate date(31, Month::DECEMBER, 2023);

        ++date;
        CHECK(date.GetDay() == 1);
        CHECK(date.GetMonth() == Month::JANUARY);

        date++;
        CHECK(date.GetDay() == 2);

        CDate d2(1, Month::JANUARY, 2024);
        --d2;
        CHECK(d2.GetYear() == 2023);

        CDate d3(1, Month::MARCH, 2020);
        d3--;
        CHECK(d3.GetDay() == 29);
    }

    SECTION("Addition")
    {
        CDate date(28, Month::FEBRUARY, 2010);

        CDate result = date + 3;
        CHECK(result.GetDay() == 3);
        CHECK(result.GetMonth() == Month::MARCH);

        CDate result2 = 3 + date;
        CHECK(result2.GetDay() == 3);
    }

    SECTION("Subtraction")
    {
        CDate d1(1, Month::JANUARY, 2010);
        CDate d2(30, Month::DECEMBER, 2009);

        CHECK((d1 - d2) == 2);
        CHECK((d2 - d1) == -2);
    }

    SECTION("Assignment operators")
    {
        CDate date(28, Month::FEBRUARY, 2010);

        date += 3;
        CHECK(date.GetMonth() == Month::MARCH);

        date -= 3;
        CHECK(date.GetMonth() == Month::FEBRUARY);
    }

    SECTION("Comparisons")
    {
        CDate d1(1, Month::JANUARY, 2020);
        CDate d2(1, Month::JANUARY, 2020);
        CDate d3(2, Month::JANUARY, 2020);

        CHECK(d1 == d2);
        CHECK(d1 != d3);
        CHECK(d1 < d3);
        CHECK(d3 > d1);
        CHECK(d1 <= d2);
        CHECK(d3 >= d1);
    }
}

TEST_CASE("Internal logic (TestAccess)")
{
    SECTION("Leap year")
    {
        CHECK(TestAccess::IsLeapYear(2020));
        CHECK_FALSE(TestAccess::IsLeapYear(2021));
        CHECK_FALSE(TestAccess::IsLeapYear(1900));
        CHECK(TestAccess::IsLeapYear(2000));
    }

    SECTION("Days in month")
    {
        CHECK(TestAccess::DaysInMonth(2020, Month::FEBRUARY) == 29);
        CHECK(TestAccess::DaysInMonth(2021, Month::FEBRUARY) == 28);
    }

    SECTION("Timestamp conversion")
    {
        CHECK(TestAccess::DateToTimestamp(1, Month::JANUARY, 1970) == 0);
        CHECK(TestAccess::DateToTimestamp(1, Month::JANUARY, 1971) == 365);

        int invalid = TestAccess::DateToTimestamp(0, Month::JANUARY, 1970);
        CHECK(invalid == -1);
    }

    SECTION("Reverse conversion")
    {
        unsigned d; Month m; unsigned y;

        TestAccess::TimestampToDate(0, d, m, y);
        CHECK(d == 1);
        CHECK(m == Month::JANUARY);
        CHECK(y == 1970);
    }
}

TEST_CASE("Controller valid scenarios")
{
    SECTION("Print date")
    {
        std::istringstream in("24.12.2020");
        std::ostringstream out;
        CDateController::ProcessCommands(in, out);
        CHECK(out.str() == "24.12.2020 (Day:24, Month:12, Year:2020, WeekDay:4)\n");
    }

    SECTION("Addition")
    {
        std::istringstream in("28.02.2010 + 3");
        std::ostringstream out;
        CDateController::ProcessCommands(in, out);
        CHECK(out.str() == "03.03.2010 (Day:3, Month:3, Year:2010, WeekDay:3)\n");
    }

    SECTION("Difference")
    {
        std::istringstream in("01.01.2010 - 30.12.2009");
        std::ostringstream out;
        CDateController::ProcessCommands(in, out);
        CHECK(out.str() == "2 days\n");
    }

    SECTION("Number first")
    {
        std::istringstream in("3 + 28.02.2010");
        std::ostringstream out;
        CDateController::ProcessCommands(in, out);
        CHECK(out.str() == "03.03.2010 (Day:3, Month:3, Year:2010, WeekDay:3)\n");
    }
}

TEST_CASE("Controller error handling")
{
    SECTION("Invalid date format")
    {
        std::istringstream in("01-01-2020");
        std::ostringstream out;
        CDateController::ProcessCommands(in, out);
        CHECK(out.str() == "ERROR: Invalid date\n");
    }

    SECTION("Invalid date value")
    {
        std::istringstream in("32.01.2020");
        std::ostringstream out;
        CDateController::ProcessCommands(in, out);
        CHECK(out.str() == "ERROR: Invalid date\n");
    }

    SECTION("Invalid operator")
    {
        std::istringstream in("01.01.2020 % 5");
        std::ostringstream out;
        CDateController::ProcessCommands(in, out);
        CHECK(out.str() == "ERROR: Unknown operator\n");
    }

    SECTION("Missing operand")
    {
        std::istringstream in("01.01.2020 +");
        std::ostringstream out;
        CDateController::ProcessCommands(in, out);
        CHECK(out.str() == "ERROR: Missing operand\n");
    }

    SECTION("Invalid second date")
    {
        std::istringstream in("01.01.2020 - 32.01.2020");
        std::ostringstream out;
        CDateController::ProcessCommands(in, out);
        CHECK(out.str() == "ERROR: Invalid date\n");
    }

    SECTION("Number first invalid operator")
    {
        std::istringstream in("3 - 01.01.2020");
        std::ostringstream out;
        CDateController::ProcessCommands(in, out);
        CHECK(out.str() == "ERROR: Unknown operator\n");
    }

    SECTION("Number + invalid date")
    {
        std::istringstream in("3 + 32.01.2020");
        std::ostringstream out;
        CDateController::ProcessCommands(in, out);
        CHECK(out.str() == "ERROR: Invalid date\n");
    }

    SECTION("Out of range result")
    {
        std::istringstream in("31.12.9999 + 1");
        std::ostringstream out;
        CDateController::ProcessCommands(in, out);
        CHECK(out.str() == "INVALID\n");
    }

    SECTION("Empty input")
    {
        std::istringstream in("");
        std::ostringstream out;
        CDateController::ProcessCommands(in, out);
        CHECK(out.str().empty());
    }
}
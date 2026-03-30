#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"
#include "CDate.h"
#include "CDateController.h"
#include <sstream>
#include <string>

TEST_CASE("CDate class tests", "[CDate]")
{
    SECTION("Constructor and basic initialization")
    {
        CDate date1;
        CHECK(date1.GetDay() == 1);
        CHECK(date1.GetMonth() == Month::JANUARY);
        CHECK(date1.GetYear() == 1970);
        CHECK(date1.GetWeekDay() == WeekDay::THURSDAY);
        CHECK(date1.IsValid() == true);
        
        CDate date2(1, Month::JANUARY, 1970);
        CHECK(date2.GetDay() == 1);
        CHECK(date2.GetMonth() == Month::JANUARY);
        CHECK(date2.GetYear() == 1970);
        CHECK(date2.IsValid() == true);
        
        CDate date3(32);
        CHECK(date3.GetDay() == 2);
        CHECK(date3.GetMonth() == Month::FEBRUARY);
        CHECK(date3.GetYear() == 1970);
        CHECK(date3.IsValid() == true);
    }
    
    SECTION("Invalid date handling")
    {
        CDate invalidDate1(0, Month::JANUARY, 1970);
        CHECK(invalidDate1.IsValid() == false);
        
        CDate invalidDate2(31, Month::FEBRUARY, 2020);
        CHECK(invalidDate2.IsValid() == false);
        
        CDate invalidDate3(1, Month::JANUARY, 1969);
        CHECK(invalidDate3.IsValid() == false);
        
        CDate invalidDate4(1, Month::JANUARY, 10000);
        CHECK(invalidDate4.IsValid() == false);
        
        CDate invalidDate5(-1);
        CHECK(invalidDate5.IsValid() == false);
        
        CDate invalidDate6(9999999);
        CHECK(invalidDate6.IsValid() == false);
    }
}

TEST_CASE("Getters tests", "[Getters]")
{
    SECTION("Standard date 23.03.2010")
    {
        CDate date(23, Month::MARCH, 2010);
        
        CHECK(date.GetDay() == 23);
        CHECK(date.GetMonth() == Month::MARCH);
        CHECK(date.GetYear() == 2010);
        CHECK(date.GetWeekDay() == WeekDay::TUESDAY);
        CHECK(date.IsValid() == true);
    }
    
    SECTION("Leap year date 29.02.2020")
    {
        CDate date(29, Month::FEBRUARY, 2020);
        
        CHECK(date.GetDay() == 29);
        CHECK(date.GetMonth() == Month::FEBRUARY);
        CHECK(date.GetYear() == 2020);
        CHECK(date.GetWeekDay() == WeekDay::SATURDAY);
        CHECK(date.IsValid() == true);
    }
    
    SECTION("End of year 31.12.2023")
    {
        CDate date(31, Month::DECEMBER, 2023);
        
        CHECK(date.GetDay() == 31);
        CHECK(date.GetMonth() == Month::DECEMBER);
        CHECK(date.GetYear() == 2023);
        CHECK(date.GetWeekDay() == WeekDay::SUNDAY);
        CHECK(date.IsValid() == true);
    }
    
    SECTION("Beginning of year 01.01.2024")
    {
        CDate date(1, Month::JANUARY, 2024);
        
        CHECK(date.GetDay() == 1);
        CHECK(date.GetMonth() == Month::JANUARY);
        CHECK(date.GetYear() == 2024);
        CHECK(date.GetWeekDay() == WeekDay::MONDAY);
        CHECK(date.IsValid() == true);
    }
}

TEST_CASE("Operators tests", "[Operators]")
{
    SECTION("Increment and decrement operators")
    {
        CDate date(31, Month::DECEMBER, 2023);
        
        CDate afterIncrement = ++date;
        CHECK(afterIncrement.GetDay() == 1);
        CHECK(afterIncrement.GetMonth() == Month::JANUARY);
        CHECK(afterIncrement.GetYear() == 2024);
        
        CDate postIncrement = date++;
        CHECK(postIncrement.GetDay() == 1);
        CHECK(postIncrement.GetMonth() == Month::JANUARY);
        CHECK(postIncrement.GetYear() == 2024);
        CHECK(date.GetDay() == 2);
        
        CDate date2(1, Month::JANUARY, 2024);
        CDate afterDecrement = --date2;
        CHECK(afterDecrement.GetDay() == 31);
        CHECK(afterDecrement.GetMonth() == Month::DECEMBER);
        CHECK(afterDecrement.GetYear() == 2023);
        
        CDate date3(1, Month::MARCH, 2020);
        CDate postDecrement = date3--;
        CHECK(postDecrement.GetDay() == 1);
        CHECK(postDecrement.GetMonth() == Month::MARCH);
        CHECK(postDecrement.GetYear() == 2020);
        CHECK(date3.GetDay() == 29);
        CHECK(date3.GetMonth() == Month::FEBRUARY);
        CHECK(date3.GetYear() == 2020);
    }
    
    SECTION("Addition operator")
    {
        CDate date(28, Month::FEBRUARY, 2010);
        CDate result1 = date + 3;
        CHECK(result1.GetDay() == 3);
        CHECK(result1.GetMonth() == Month::MARCH);
        CHECK(result1.GetYear() == 2010);
        
        CDate result2 = 3 + date;
        CHECK(result2.GetDay() == 3);
        CHECK(result2.GetMonth() == Month::MARCH);
        CHECK(result2.GetYear() == 2010);
        
        CDate date2(31, Month::DECEMBER, 2023);
        CDate result3 = date2 + 1;
        CHECK(result3.GetDay() == 1);
        CHECK(result3.GetMonth() == Month::JANUARY);
        CHECK(result3.GetYear() == 2024);
        
        CDate date3(1, Month::JANUARY, 1970);
        CDate result4 = date3 + 365;
        CHECK(result4.GetDay() == 1);
        CHECK(result4.GetMonth() == Month::JANUARY);
        CHECK(result4.GetYear() == 1971);
    }
    
    SECTION("Subtraction operator")
    {
        CDate date(1, Month::JANUARY, 2010);
        CDate result1 = date - 2;
        CHECK(result1.GetDay() == 30);
        CHECK(result1.GetMonth() == Month::DECEMBER);
        CHECK(result1.GetYear() == 2009);
        
        CDate date2(3, Month::MARCH, 2010);
        CDate date3(28, Month::FEBRUARY, 2010);
        int diff1 = date2 - date3;
        CHECK(diff1 == 3);
        
        CDate date4(1, Month::JANUARY, 2010);
        CDate date5(3, Month::JANUARY, 2010);
        int diff2 = date4 - date5;
        CHECK(diff2 == -2);
        
        CDate date6(1, Month::MARCH, 2020);
        CDate date7(1, Month::MARCH, 2019);
        int diff3 = date6 - date7;
        CHECK(diff3 == 366);
    }
    
    SECTION("Addition assignment operator")
    {
        CDate date(28, Month::FEBRUARY, 2010);
        date += 3;
        CHECK(date.GetDay() == 3);
        CHECK(date.GetMonth() == Month::MARCH);
        CHECK(date.GetYear() == 2010);
        
        CDate date2(31, Month::DECEMBER, 2023);
        date2 += 1;
        CHECK(date2.GetDay() == 1);
        CHECK(date2.GetMonth() == Month::JANUARY);
        CHECK(date2.GetYear() == 2024);
    }
    
    SECTION("Subtraction assignment operator")
    {
        CDate date(1, Month::JANUARY, 2010);
        date -= 2;
        CHECK(date.GetDay() == 30);
        CHECK(date.GetMonth() == Month::DECEMBER);
        CHECK(date.GetYear() == 2009);
        
        CDate date2(1, Month::MARCH, 2020);
        date2 -= 1;
        CHECK(date2.GetDay() == 29);
        CHECK(date2.GetMonth() == Month::FEBRUARY);
        CHECK(date2.GetYear() == 2020);
    }
    
    SECTION("Comparison operators")
    {
        CDate date1(1, Month::JANUARY, 2020);
        CDate date2(1, Month::JANUARY, 2020);
        CDate date3(2, Month::JANUARY, 2020);
        CDate date4(31, Month::DECEMBER, 2019);
        
        CHECK((date1 == date2) == true);
        CHECK((date1 == date3) == false);
        CHECK((date1 != date3) == true);
        CHECK((date1 != date2) == false);
        
        CHECK((date1 < date3) == true);
        CHECK((date1 < date4) == false);
        CHECK((date3 > date1) == true);
        CHECK((date4 > date1) == false);
        
        CHECK((date1 <= date2) == true);
        CHECK((date1 <= date3) == true);
        CHECK((date1 <= date4) == false);
        CHECK((date1 >= date2) == true);
        CHECK((date3 >= date1) == true);
        CHECK((date4 >= date1) == false);
    }
}

TEST_CASE("Individual functions tests", "[IndividualFunctions]")
{
    SECTION("IsLeapYear function")
    {
        CHECK(TestAccess::IsLeapYear(2020) == true);
        CHECK(TestAccess::IsLeapYear(2021) == false);
        CHECK(TestAccess::IsLeapYear(1900) == false);
        CHECK(TestAccess::IsLeapYear(2000) == true);
        CHECK(TestAccess::IsLeapYear(2024) == true);
        CHECK(TestAccess::IsLeapYear(2023) == false);
    }
    
    SECTION("DaysInMonth function")
    {
        CHECK(TestAccess::DaysInMonth(2020, Month::JANUARY) == 31);
        CHECK(TestAccess::DaysInMonth(2020, Month::FEBRUARY) == 29);
        CHECK(TestAccess::DaysInMonth(2021, Month::FEBRUARY) == 28);
        CHECK(TestAccess::DaysInMonth(2020, Month::APRIL) == 30);
        CHECK(TestAccess::DaysInMonth(2020, Month::DECEMBER) == 31);
    }
    
    SECTION("DateToTimestamp function")
    {
        int timestamp1 = TestAccess::DateToTimestamp(1, Month::JANUARY, 1970);
        CHECK(timestamp1 == 0);
        
        int timestamp2 = TestAccess::DateToTimestamp(2, Month::JANUARY, 1970);
        CHECK(timestamp2 == 1);
        
        int timestamp3 = TestAccess::DateToTimestamp(1, Month::FEBRUARY, 1970);
        CHECK(timestamp3 == 31);
        
        int timestamp4 = TestAccess::DateToTimestamp(1, Month::JANUARY, 1971);
        CHECK(timestamp4 == 365);
        
        int invalidTimestamp = TestAccess::DateToTimestamp(0, Month::JANUARY, 1970);
        CHECK(invalidTimestamp == -1);
    }
    
    SECTION("TimestampToDate function")
    {
        unsigned day;
        Month month;
        unsigned year;
        
        TestAccess::TimestampToDate(0, day, month, year);
        CHECK(day == 1);
        CHECK(month == Month::JANUARY);
        CHECK(year == 1970);
        
        TestAccess::TimestampToDate(31, day, month, year);
        CHECK(day == 1);
        CHECK(month == Month::FEBRUARY);
        CHECK(year == 1970);
        
        TestAccess::TimestampToDate(365, day, month, year);
        CHECK(day == 1);
        CHECK(month == Month::JANUARY);
        CHECK(year == 1971);
        
        TestAccess::TimestampToDate(-1, day, month, year);
        CHECK(day == 0);
        CHECK(year == 0);
    }
    
    SECTION("CalculateWeekDay function")
    {
        WeekDay day1 = TestAccess::CalculateWeekDay(0);
        CHECK(day1 == WeekDay::THURSDAY);
        
        WeekDay day2 = TestAccess::CalculateWeekDay(1);
        CHECK(day2 == WeekDay::FRIDAY);
        
        WeekDay day3 = TestAccess::CalculateWeekDay(6);
        CHECK(day3 == WeekDay::WEDNESDAY);
        
        WeekDay day4 = TestAccess::CalculateWeekDay(7);
        CHECK(day4 == WeekDay::THURSDAY);
    }
}

TEST_CASE("ProcessCommands tests", "[ProcessCommands]")
{
    SECTION("Print date with details")
    {
        std::istringstream input("24.12.2020");
        std::ostringstream output;
        CDateController::ProcessCommands(input, output);
        CHECK(output.str() == "24.12.2020 (Day:24, Month:12, Year:2020, WeekDay:4)\n");
    }
    
    SECTION("Addition operations")
    {
        std::istringstream input("28.02.2010 + 3");
        std::ostringstream output;
        CDateController::ProcessCommands(input, output);
        CHECK(output.str() == "03.03.2010 (Day:3, Month:3, Year:2010, WeekDay:3)\n");
    }
    
    SECTION("Subtraction operations - days")
    {
        std::istringstream input("01.01.2010 - 2");
        std::ostringstream output;
        CDateController::ProcessCommands(input, output);
        std::string result = output.str();
        CHECK(result.find("30.12.2009") != std::string::npos);
        CHECK(result.find("Day:30") != std::string::npos);
        CHECK(result.find("Month:12") != std::string::npos);
        CHECK(result.find("Year:2009") != std::string::npos);
    }
    
    SECTION("Subtraction operations - dates")
    {
        std::istringstream input("01.01.2010 - 30.12.2009");
        std::ostringstream output;
        CDateController::ProcessCommands(input, output);
        CHECK(output.str() == "2 days\n");
    }
    
    SECTION("Increment operations")
    {
        std::istringstream input("31.12.2023 ++");
        std::ostringstream output;
        CDateController::ProcessCommands(input, output);
        CHECK(output.str() == "01.01.2024 (Day:1, Month:1, Year:2024, WeekDay:1)\n");
    }
    
    SECTION("Decrement operations")
    {
        std::istringstream input("01.01.2024 --");
        std::ostringstream output;
        CDateController::ProcessCommands(input, output);
        CHECK(output.str() == "31.12.2023 (Day:31, Month:12, Year:2023, WeekDay:0)\n");
    }
    
    SECTION("Number plus date format")
    {
        std::istringstream input("3 + 28.02.2010");
        std::ostringstream output;
        CDateController::ProcessCommands(input, output);
        CHECK(output.str() == "03.03.2010 (Day:3, Month:3, Year:2010, WeekDay:3)\n");
    }
}

TEST_CASE("Error handling tests", "[Errors]")
{
    SECTION("Invalid input format")
    {
        std::istringstream input("01-01-2020");
        std::ostringstream output;
        CDateController::ProcessCommands(input, output);
        CHECK(output.str() == "ERROR: Invalid date\nINVALID\n");
    }
    
    SECTION("Unknown operator error")
    {
        std::istringstream input("01.01.2020 % 5");
        std::ostringstream output;
        CDateController::ProcessCommands(input, output);
        std::string result = output.str();
        CHECK(result.find("ERROR: Unknown operator") != std::string::npos);
        CHECK(result.find("INVALID") != std::string::npos);
    }
    
    SECTION("Invalid increment on invalid date")
    {
        std::istringstream input("32.01.2020 ++");
        std::ostringstream output;
        CDateController::ProcessCommands(input, output);
        CHECK(output.str() == "ERROR: Invalid date\nINVALID\n");
    }
    
    SECTION("Invalid decrement on invalid date")
    {
        std::istringstream input("32.01.2020 --");
        std::ostringstream output;
        CDateController::ProcessCommands(input, output);
        CHECK(output.str() == "ERROR: Invalid date\nINVALID\n");
    }
    
    SECTION("Invalid year error")
    {
        std::istringstream input("01.01.1969");
        std::ostringstream output;
        CDateController::ProcessCommands(input, output);
        CHECK(output.str() == "ERROR: Invalid date\nINVALID\n");
    }
    
    SECTION("Invalid day error")
    {
        std::istringstream input("32.01.2020");
        std::ostringstream output;
        CDateController::ProcessCommands(input, output);
        CHECK(output.str() == "ERROR: Invalid date\nINVALID\n");
    }
    
    SECTION("Missing operand error")
    {
        std::istringstream input("01.01.2020 +");
        std::ostringstream output;
        CDateController::ProcessCommands(input, output);
        CHECK(output.str() == "ERROR: Missing operand\nINVALID\n");
    }
    
    SECTION("Missing date operand error")
    {
        std::istringstream input("01.01.2020 -");
        std::ostringstream output;
        CDateController::ProcessCommands(input, output);
        CHECK(output.str() == "ERROR: Missing operand\nINVALID\n");
    }
    
    SECTION("Comparison with invalid date")
    {
        std::istringstream input("32.01.2020 == 01.01.2020");
        std::ostringstream output;
        CDateController::ProcessCommands(input, output);
        CHECK(output.str() == "ERROR: Invalid date\nINVALID\n");
    }
    
    SECTION("Subtraction with invalid date")
    {
        std::istringstream input("32.01.2020 - 01.01.2020");
        std::ostringstream output;
        CDateController::ProcessCommands(input, output);
        CHECK(output.str() == "ERROR: Invalid date\nINVALID\n");
    }
    
    SECTION("Result out of valid range")
    {
        std::istringstream input("31.12.9999 + 1");
        std::ostringstream output;
        CDateController::ProcessCommands(input, output);
        CHECK(output.str() == "INVALID\n");
    }
    
    SECTION("Empty input handling")
    {
        std::istringstream input("");
        std::ostringstream output;
        CDateController::ProcessCommands(input, output);
        CHECK(output.str() == "");
    }
}
#pragma once
#include <iostream>

enum class Month
{
    JANUARY = 1, FEBRUARY, MARCH, APRIL,
    MAY, JUNE, JULY, AUGUST, SEPTEMBER,
    OCTOBER, NOVEMBER, DECEMBER
};

enum class WeekDay
{
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
    THURSDAY, FRIDAY, SATURDAY
};

class CDate
{
public:
    CDate(unsigned day, Month month, unsigned year);
    explicit CDate(unsigned timestamp);
    CDate();

    unsigned GetDay() const;
    Month GetMonth() const;
    unsigned GetYear() const;
    WeekDay GetWeekDay() const;

    bool IsValid() const;
    CDate operator+(int days) const;
    CDate operator-(int days) const;
    CDate& operator++();
    CDate operator++(int);
    CDate& operator--();
    CDate operator--(int);

    friend CDate operator+(int days, const CDate& date);
    int operator-(const CDate& other) const;

    CDate& operator+=(int days);
    CDate& operator-=(int days);

    bool operator==(const CDate& other) const;
    bool operator!=(const CDate& other) const;
    bool operator<(const CDate& other) const;
    bool operator>(const CDate& other) const;
    bool operator<=(const CDate& other) const;
    bool operator>=(const CDate& other) const;

    friend std::ostream& operator<<(std::ostream& os, const CDate& date);
    friend std::istream& operator>>(std::istream& is, CDate& date);

private:
    int m_timestamp = 0;

    static bool IsLeapYear(unsigned year);
    static unsigned DaysInMonth(unsigned year, Month month);
    static int DateToTimestamp(unsigned day, Month month, unsigned year);
    static void TimestampToDate(int timestamp, unsigned& day, Month& month, unsigned& year);
    static WeekDay CalculateWeekDay(int timestamp);

    friend struct TestAccess;
};

struct TestAccess
{
    static bool IsLeapYear(unsigned year) { return CDate::IsLeapYear(year); }
    static unsigned DaysInMonth(unsigned year, Month month) { return CDate::DaysInMonth(year, month); }
    static int DateToTimestamp(unsigned day, Month month, unsigned year) { return CDate::DateToTimestamp(day, month, year); }
    static void TimestampToDate(int timestamp, unsigned& day, Month& month, unsigned& year) { CDate::TimestampToDate(timestamp, day, month, year); }
    static WeekDay CalculateWeekDay(int timestamp) { return CDate::CalculateWeekDay(timestamp); }
};
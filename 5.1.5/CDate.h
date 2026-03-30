#pragma once
#include <iostream>

// Месяц
enum class Month
{
    JANUARY = 1, FEBRUARY, MARCH, APRIL,
    MAY, JUNE, JULY, AUGUST, SEPTEMBER,
    OCTOBER, NOVEMBER, DECEMBER
};

// День недели
enum class WeekDay
{
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
    THURSDAY, FRIDAY, SATURDAY
};

class CDate
{
public:
    // Конструкторы
    CDate(unsigned day, Month month, unsigned year);
    explicit CDate(unsigned timestamp);
    CDate();

    // Геттеры
    unsigned GetDay() const;
    Month GetMonth() const;
    unsigned GetYear() const;
    WeekDay GetWeekDay() const;

    // Проверка валидности
    bool IsValid() const;

    // Инкремент / декремент
    CDate& operator++();      // префикс
    CDate operator++(int);    // постфикс

    CDate& operator--();
    CDate operator--(int);

    // Арифметика
    CDate operator+(int days) const;
    friend CDate operator+(int days, const CDate& date);

    CDate operator-(int days) const;
    int operator-(const CDate& other) const;

    CDate& operator+=(int days);
    CDate& operator-=(int days);

    // Сравнения
    bool operator==(const CDate& other) const;
    bool operator!=(const CDate& other) const;

    bool operator<(const CDate& other) const;
    bool operator>(const CDate& other) const;
    bool operator<=(const CDate& other) const;
    bool operator>=(const CDate& other) const;

    // Ввод / вывод
    friend std::ostream& operator<<(std::ostream& os, const CDate& date);
    friend std::istream& operator>>(std::istream& is, CDate& date);

private:
    int m_timestamp = 0; // дни с 01.01.1970

private:
    // Вспомогательные функции
    static bool IsLeapYear(unsigned year);
    static unsigned DaysInMonth(unsigned year, Month month);

    static int DateToTimestamp(unsigned day, Month month, unsigned year);
    static void TimestampToDate(int timestamp, unsigned& day, Month& month, unsigned& year);

    static WeekDay CalculateWeekDay(int timestamp);
};
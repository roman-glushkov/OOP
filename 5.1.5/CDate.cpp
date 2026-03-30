#include "CDate.h"
#include "Config.h"

bool CDate::IsLeapYear(unsigned year)
{
    return (year % Config::LEAP_YEAR_DIVISOR_4 == Config::ZERO && 
            year % Config::LEAP_YEAR_DIVISOR_100 != Config::ZERO) || 
           (year % Config::LEAP_YEAR_DIVISOR_400 == Config::ZERO);
}

unsigned CDate::DaysInMonth(unsigned year, Month month)
{
    switch (month)
    {
    case Month::JANUARY:   return Config::DAYS_IN_JANUARY;
    case Month::FEBRUARY:  return IsLeapYear(year) ? Config::DAYS_IN_FEBRUARY_LEAP : Config::DAYS_IN_FEBRUARY_NORMAL;
    case Month::MARCH:     return Config::DAYS_IN_MARCH;
    case Month::APRIL:     return Config::DAYS_IN_APRIL;
    case Month::MAY:       return Config::DAYS_IN_MAY;
    case Month::JUNE:      return Config::DAYS_IN_JUNE;
    case Month::JULY:      return Config::DAYS_IN_JULY;
    case Month::AUGUST:    return Config::DAYS_IN_AUGUST;
    case Month::SEPTEMBER: return Config::DAYS_IN_SEPTEMBER;
    case Month::OCTOBER:   return Config::DAYS_IN_OCTOBER;
    case Month::NOVEMBER:  return Config::DAYS_IN_NOVEMBER;
    case Month::DECEMBER:  return Config::DAYS_IN_DECEMBER;
    default:               return Config::ZERO;
    }
}

int CDate::DateToTimestamp(unsigned day, Month month, unsigned year)
{
    if (year < Config::MIN_YEAR || year > Config::MAX_YEAR)
        return Config::INVALID_TIMESTAMP;

    if (day == Config::ZERO_DAY || day > DaysInMonth(year, month))
        return Config::INVALID_TIMESTAMP;

    int days = Config::ZERO;

    for (unsigned y = Config::MIN_YEAR; y < year; ++y)
    {
        days += IsLeapYear(y) ? Config::LEAP_YEAR_EXTRA_DAYS : Config::NORMAL_YEAR_DAYS;
    }

    for (int m = Config::FIRST_MONTH; m < static_cast<int>(month); ++m)
    {
        days += DaysInMonth(year, static_cast<Month>(m));
    }

    days += day - Config::DAY_OFFSET;

    return days;
}

void CDate::TimestampToDate(int timestamp, unsigned& day, Month& month, unsigned& year)
{
    if (timestamp < Config::MIN_TIMESTAMP)
    {
        day = Config::INVALID_DAY;
        month = Month::JANUARY;
        year = Config::INVALID_YEAR;
        return;
    }

    int days = timestamp;
    int y = Config::MIN_YEAR;

    while (true)
    {
        int daysInYear = IsLeapYear(y) ? Config::LEAP_YEAR_EXTRA_DAYS : Config::NORMAL_YEAR_DAYS;
        if (days < daysInYear)
            break;

        days -= daysInYear;
        ++y;
    }

    year = y;

    int m = Config::FIRST_MONTH;
    while (true)
    {
        int dim = DaysInMonth(year, static_cast<Month>(m));
        if (days < dim)
            break;

        days -= dim;
        ++m;
    }

    month = static_cast<Month>(m);
    day = days + Config::TIMESTAMP_TO_DAY_OFFSET;
}

WeekDay CDate::CalculateWeekDay(int timestamp)
{
    int d = (Config::EPOCH_WEEKDAY + timestamp) % Config::DAYS_IN_WEEK;
    if (d < Config::WEEKDAY_MIN) 
        d += Config::DAYS_IN_WEEK;
    return static_cast<WeekDay>(d);
}

CDate::CDate() : m_timestamp(Config::MIN_TIMESTAMP)
{
}

CDate::CDate(unsigned timestamp)
{
    m_timestamp = static_cast<int>(timestamp);
    if (!IsValid())
        m_timestamp = Config::INVALID_TIMESTAMP;
}

CDate::CDate(unsigned day, Month month, unsigned year)
{
    m_timestamp = DateToTimestamp(day, month, year);
}

unsigned CDate::GetDay() const
{
    unsigned d, y;
    Month m;
    TimestampToDate(m_timestamp, d, m, y);
    return d;
}

Month CDate::GetMonth() const
{
    unsigned d, y;
    Month m;
    TimestampToDate(m_timestamp, d, m, y);
    return m;
}

unsigned CDate::GetYear() const
{
    unsigned d, y;
    Month m;
    TimestampToDate(m_timestamp, d, m, y);
    return y;
}

WeekDay CDate::GetWeekDay() const
{
    return CalculateWeekDay(m_timestamp);
}

bool CDate::IsValid() const
{
    if (m_timestamp < Config::MIN_TIMESTAMP)
        return false;

    unsigned d, y;
    Month m;
    TimestampToDate(m_timestamp, d, m, y);

    if (y < Config::MIN_YEAR || y > Config::MAX_YEAR)
        return false;

    if (d == Config::ZERO_DAY || d > DaysInMonth(y, m))
        return false;

    return true;
}

CDate& CDate::operator++()
{
    if (IsValid())
    {
        ++m_timestamp;
        if (!IsValid())
            m_timestamp = Config::INVALID_TIMESTAMP;
    }
    return *this;
}

CDate CDate::operator++(int)
{
    CDate tmp = *this;
    ++(*this);
    return tmp;
}

CDate& CDate::operator--()
{
    if (IsValid())
    {
        --m_timestamp;
        if (m_timestamp < Config::MIN_TIMESTAMP || !IsValid())
            m_timestamp = Config::INVALID_TIMESTAMP;
    }
    return *this;
}

CDate CDate::operator--(int)
{
    CDate tmp = *this;
    --(*this);
    return tmp;
}

CDate CDate::operator+(int days) const
{
    if (!IsValid())
        return *this;

    CDate result = *this;
    result.m_timestamp += days;

    if (result.m_timestamp < Config::MIN_TIMESTAMP || !result.IsValid())
        result.m_timestamp = Config::INVALID_TIMESTAMP;

    return result;
}

CDate operator+(int days, const CDate& date)
{
    return date + days;
}

CDate CDate::operator-(int days) const
{
    return *this + (-days);
}

int CDate::operator-(const CDate& other) const
{
    if (!IsValid() || !other.IsValid())
        return Config::ZERO;
    return m_timestamp - other.m_timestamp;
}

CDate& CDate::operator+=(int days)
{
    if (IsValid())
    {
        m_timestamp += days;
        if (m_timestamp < Config::MIN_TIMESTAMP || !IsValid())
            m_timestamp = Config::INVALID_TIMESTAMP;
    }
    return *this;
}

CDate& CDate::operator-=(int days)
{
    return (*this += -days);
}

bool CDate::operator==(const CDate& other) const
{
    return m_timestamp == other.m_timestamp;
}

bool CDate::operator!=(const CDate& other) const
{
    return !(*this == other);
}

bool CDate::operator<(const CDate& other) const
{
    return m_timestamp < other.m_timestamp;
}

bool CDate::operator>(const CDate& other) const
{
    return m_timestamp > other.m_timestamp;
}

bool CDate::operator<=(const CDate& other) const
{
    return !(*this > other);
}

bool CDate::operator>=(const CDate& other) const
{
    return !(*this < other);
}

std::ostream& operator<<(std::ostream& os, const CDate& date)
{
    if (!date.IsValid())
    {
        os << Config::RESULT_INVALID;
        return os;
    }

    unsigned d = date.GetDay();
    unsigned y = date.GetYear();
    Month m = date.GetMonth();

    if (d < Config::SINGLE_DIGIT)
        os << Config::ZERO_FILL;
    os << d << Config::DATE_SEPARATOR;
    
    if (static_cast<int>(m) < Config::SINGLE_DIGIT)
        os << Config::ZERO_FILL;
    os << static_cast<int>(m) << Config::DATE_SEPARATOR;
    
    if (y < Config::THREE_DIGITS)
        os << Config::ZERO_FILL;
    if (y < Config::TWO_DIGITS)
        os << Config::ZERO_FILL;
    if (y < Config::ONE_DIGIT)
        os << Config::ZERO_FILL;
    os << y;

    return os;
}

std::istream& operator>>(std::istream& is, CDate& date)
{
    unsigned d, m, y;
    char dot1, dot2;

    if (is >> d >> dot1 >> m >> dot2 >> y && dot1 == Config::DATE_SEPARATOR && dot2 == Config::DATE_SEPARATOR)
    {
        CDate tmp(d, static_cast<Month>(m), y);
        if (tmp.IsValid())
            date = tmp;
        else
            date.m_timestamp = Config::INVALID_TIMESTAMP;
    }
    else
    {
        date.m_timestamp = Config::INVALID_TIMESTAMP;
    }

    return is;
}
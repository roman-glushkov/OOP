#include "CDate.h"

static int CountLeapYears(unsigned year)
{
    year--;
    return year / 4 - year / 100 + year / 400;
}

bool CDate::IsLeapYear(unsigned year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

unsigned CDate::DaysInMonth(unsigned year, Month month)
{
    switch (month)
    {
    case Month::JANUARY: return 31;
    case Month::FEBRUARY: return IsLeapYear(year) ? 29 : 28;
    case Month::MARCH: return 31;
    case Month::APRIL: return 30;
    case Month::MAY: return 31;
    case Month::JUNE: return 30;
    case Month::JULY: return 31;
    case Month::AUGUST: return 31;
    case Month::SEPTEMBER: return 30;
    case Month::OCTOBER: return 31;
    case Month::NOVEMBER: return 30;
    case Month::DECEMBER: return 31;
    default: return 0;
    }
}

int CDate::DateToTimestamp(unsigned day, Month month, unsigned year)
{
    if (year < 1970 || year > 9999)
        return -1;

    if (day == 0 || day > DaysInMonth(year, month))
        return -1;

    int yearsPassed = year - 1970;

    int leapYears =
        CountLeapYears(year) - CountLeapYears(1970);

    int days = yearsPassed * 365 + leapYears;

    static const int daysBeforeMonth[] =
    {
        0,
        0,
        31,
        59,
        90,
        120,
        151,
        181,
        212,
        243,
        273,
        304,
        334
    };

    days += daysBeforeMonth[static_cast<int>(month)];

    if (month > Month::FEBRUARY && IsLeapYear(year))
        days += 1;

    days += day - 1;

    return days;
}

void CDate::TimestampToDate(int timestamp, unsigned& day, Month& month, unsigned& year)
{
    if (timestamp < 0)
    {
        day = 0;
        month = Month::JANUARY;
        year = 0;
        return;
    }

    int days = timestamp;

    int y = 1970;

    int cycles400 = days / 146097;
    y += cycles400 * 400;
    days %= 146097;

    int cycles100 = days / 36524;
    if (cycles100 == 4) cycles100 = 3;
    y += cycles100 * 100;
    days -= cycles100 * 36524;

    int cycles4 = days / 1461;
    y += cycles4 * 4;
    days %= 1461;

    int cycles1 = days / 365;
    if (cycles1 == 4) cycles1 = 3;
    y += cycles1;
    days -= cycles1 * 365;

    year = y;

    int m = 1;
    while (true)
    {
        int dim = DaysInMonth(year, static_cast<Month>(m));
        if (days < dim)
            break;

        days -= dim;
        ++m;
    }

    month = static_cast<Month>(m);
    day = days + 1;
}

WeekDay CDate::CalculateWeekDay(int timestamp)
{
    int d = (4 + timestamp) % 7;
    if (d < 0) d += 7;
    return static_cast<WeekDay>(d);
}

CDate::CDate()
    : m_timestamp(0)
{
}

CDate::CDate(unsigned timestamp)
    : m_timestamp(static_cast<int>(timestamp))
{
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
    if (m_timestamp < 0)
        return false;

    unsigned d, y;
    Month m;
    TimestampToDate(m_timestamp, d, m, y);

    return y >= 1970 && y <= 9999;
}

CDate& CDate::operator++()
{
    if (IsValid())
    {
        ++m_timestamp;
        if (!IsValid())
            m_timestamp = -1;
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
        if (!IsValid())
            m_timestamp = -1;
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

    if (!result.IsValid())
        result.m_timestamp = -1;

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
    return m_timestamp - other.m_timestamp;
}

CDate& CDate::operator+=(int days)
{
    if (IsValid())
    {
        m_timestamp += days;
        if (!IsValid())
            m_timestamp = -1;
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
        os << "INVALID";
        return os;
    }

    unsigned d = date.GetDay();
    unsigned y = date.GetYear();
    Month m = date.GetMonth();

    os << (d < 10 ? "0" : "") << d << "."
       << (static_cast<int>(m) < 10 ? "0" : "") << static_cast<int>(m) << "."
       << y;

    return os;
}

std::istream& operator>>(std::istream& is, CDate& date)
{
    unsigned d, m, y;
    char dot1, dot2;

    if (is >> d >> dot1 >> m >> dot2 >> y && dot1 == '.' && dot2 == '.')
    {
        date = CDate(d, static_cast<Month>(m), y);
    }
    else
    {
        date.m_timestamp = -1;
    }

    return is;
}
#include "CDate.h" // используем классы
#include "Config.h"

bool CDate::IsLeapYear(unsigned year) // функция на проверку вискосного года
{
    return (year % Config::LEAP_YEAR_DIVISOR_4 == Config::ZERO && year % Config::LEAP_YEAR_DIVISOR_100 != Config::ZERO) || 
    (year % Config::LEAP_YEAR_DIVISOR_400 == Config::ZERO); // просто проверка деления на 400 100 и 4
}

unsigned CDate::DaysInMonth(unsigned year, Month month) // функция для превращения дня в месяц
{
    switch (month)
    {
    case Month::JANUARY:   return Config::DAYS_IN_JANUARY; // просто выводим количетсво дней месяца
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

int CDate::DateToTimestamp(unsigned day, Month month, unsigned year) // дфункция закидывания даты в переменную там ту степ
{
    if (year < Config::MIN_YEAR || year > Config::MAX_YEAR) // проверка
        return Config::INVALID_TIMESTAMP;

    if (day == Config::ZERO_DAY || day > DaysInMonth(year, month)) // проверка
        return Config::INVALID_TIMESTAMP;

    int days = Config::ZERO; // создаем переменную день пока 0

    for (unsigned y = Config::MIN_YEAR; y < year; ++y)  // присваем y - минимальный год 1970, и пока минимальный год меньше того который введен увеличиваем минимальку
    {
        days += IsLeapYear(y) ? Config::LEAP_YEAR_EXTRA_DAYS : Config::NORMAL_YEAR_DAYS; // цикл суммирования всех дней в каждом году
    }

    for (int m = Config::FIRST_MONTH; m < static_cast<int>(month); ++m) // м присваем 1, и пока м меньше того количетсво мясяцев то идет увеличение m  
    {
        days += DaysInMonth(year, static_cast<Month>(m)); // суммируем все дни месяца, которые мы получаем функцией DaysInMonth 
    }

    days += day - Config::DAY_OFFSET; // суммируем все дни (какие мы получили из месяца и года + дни которые были прописны) но вычитаем 1

    return days; // вывод
}

void CDate::TimestampToDate(int timestamp, unsigned& day, Month& month, unsigned& year) // получаем число дней, ссылку на дни, ссылку на месяц, ссылку на год
{
    if (timestamp < Config::MIN_TIMESTAMP) // проверка на меньше 0 
    {
        day = Config::INVALID_DAY;
        month = Month::JANUARY;
        year = Config::INVALID_YEAR;
        return;
    } // записываем стандартные переменные

    int days = timestamp; // присваиваем значение в дайс
    int y = Config::MIN_YEAR; // y - 1970

    while (true) // цикл нахождения года, пока в days хранится больше дней чем в году больше 366 условно, то выполняется уменьшение в зависимости от високосного года. И какой год пишется в y
    {
        int daysInYear = IsLeapYear(y) ? Config::LEAP_YEAR_EXTRA_DAYS : Config::NORMAL_YEAR_DAYS;
        if (days < daysInYear)
            break;

        days -= daysInYear;
        ++y;
    }

    year = y; // количество лет записывается в year

    int m = Config::FIRST_MONTH; // м- 1
    while (true) // точно такой же цикл только с месяцами
    {
        int dim = DaysInMonth(year, static_cast<Month>(m));
        if (days < dim)
            break;

        days -= dim;
        ++m; // идёт запись в m
    }

    month = static_cast<Month>(m); // кладется количетсво месяцев 
    day = days + Config::TIMESTAMP_TO_DAY_OFFSET; // записывается остаток дней + 1
}

WeekDay CDate::CalculateWeekDay(int timestamp) // вычисление дня недели 
{
    int d = (Config::EPOCH_WEEKDAY + timestamp) % Config::DAYS_IN_WEEK; // начальный день был 4 + нынешнее количетсво дней, записываем остаток от деления на 7
    if (d < Config::WEEKDAY_MIN) // проверка
        d += Config::DAYS_IN_WEEK;
    return static_cast<WeekDay>(d);
}

CDate::CDate() : m_timestamp(Config::MIN_TIMESTAMP)
{// Создаёт: дату 01.01.1970 (timestamp = 0)
}

CDate::CDate(unsigned timestamp) // создаёт дату соотсвеющую количетсво дням от начала
{
    m_timestamp = static_cast<int>(timestamp);
    if (!IsValid())
        m_timestamp = Config::INVALID_TIMESTAMP;
}

CDate::CDate(unsigned day, Month month, unsigned year) // создаёт дату дд.мм.гггг
{
    m_timestamp = DateToTimestamp(day, month, year);
}

//CDate d1; 01.01.1970
//CDate d2(20000);дата через 20000 дней
//CDate d3(25, Month::DECEMBER, 2024);25.12.2024

unsigned CDate::GetDay() const // геттер для вывода дней 
{
    unsigned d, y;
    Month m;
    TimestampToDate(m_timestamp, d, m, y);
    return d; // вывод дней 
}

Month CDate::GetMonth() const // также как и день вывод месяца
{
    unsigned d, y;
    Month m;
    TimestampToDate(m_timestamp, d, m, y);
    return m;
}

unsigned CDate::GetYear() const // вывод года
{
    unsigned d, y;
    Month m;
    TimestampToDate(m_timestamp, d, m, y);
    return y;
}

WeekDay CDate::GetWeekDay() const // вывод дня недели
{
    return CalculateWeekDay(m_timestamp); // с помощью доп функции
}

bool CDate::IsValid() const // функция на проверку валидности даты
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
  // операторы пошли
CDate& CDate::operator++() // выводим ссылку на объект
{
    if (IsValid())
    {
        ++m_timestamp;
        if (!IsValid())
            m_timestamp = Config::INVALID_TIMESTAMP;
    }
    return *this;
}

CDate CDate::operator++(int) // выводим копию
{
    CDate tmp = *this;
    ++(*this);
    return tmp;
}

CDate& CDate::operator--() // точно также
{
    if (IsValid())
    {
        --m_timestamp;
        if (m_timestamp < Config::MIN_TIMESTAMP || !IsValid())
            m_timestamp = Config::INVALID_TIMESTAMP;
    }
    return *this;
}

CDate CDate::operator--(int) //  акже
{
    CDate tmp = *this;
    --(*this);
    return tmp;
}

CDate CDate::operator+(int days) const // оператор сложения дата + число
{
    if (!IsValid()) // проверка валидности
        return *this;

    CDate result = *this; // результату присваиваем сам объект - дату
    result.m_timestamp += days; // складываем к результату все дни

    if (result.m_timestamp < Config::MIN_TIMESTAMP || !result.IsValid()) // проверка что меньше 0 и валиднось выкидываем ошибку
        result.m_timestamp = Config::INVALID_TIMESTAMP;

    return result; // выводим результат
}

CDate operator+(int days, const CDate& date) // число + дата
{
    return date + days; // складываем через оператор +
}

CDate CDate::operator-(int days) const // дата - день
{
    return *this + (-days); // также через +
}

int CDate::operator-(const CDate& other) const
{
    if (!IsValid() || !other.IsValid()) // проверка на валидность двух дат
        return Config::ZERO;
    return m_timestamp - other.m_timestamp; // вычитаем количетсов дней из даты другую 
}

CDate& CDate::operator+=(int days)
{
    if (IsValid()) // валидность
    {
        m_timestamp += days; // прибавляем количетсво дней
        if (m_timestamp < Config::MIN_TIMESTAMP || !IsValid()) // проверка на больше 0
            m_timestamp = Config::INVALID_TIMESTAMP;
    }
    return *this; // выводим само число
}

CDate& CDate::operator-=(int days)
{
    return (*this += -days); // используем оператор +=
}

bool CDate::operator==(const CDate& other) const // функция которая создает новую константу
{
    return m_timestamp == other.m_timestamp; //записывает вывод проверки равентсва
}

bool CDate::operator!=(const CDate& other) const
{
    return !(*this == other); // вывод проверки == меняем !
}

bool CDate::operator<(const CDate& other) const
{
    return m_timestamp < other.m_timestamp; // проверка на <
}

bool CDate::operator>(const CDate& other) const
{
    return m_timestamp > other.m_timestamp; // также как и выше
}

bool CDate::operator<=(const CDate& other) const
{
    return !(*this > other); // используем знак больше, чтобы получить меньше либо равно
}

bool CDate::operator>=(const CDate& other) const
{
    return !(*this < other); // в обратную торону
}

std::ostream& operator<<(std::ostream& os, const CDate& date) // оператор вывода, получаем os как вывод, и константая сама дата
{
    if (!date.IsValid()) //проверка даты на валидность
    {
        os << Config::RESULT_INVALID; // выводим ошибку
        return os;
    }

    unsigned d = date.GetDay(); // находим дату, месяц и год
    unsigned y = date.GetYear();
    Month m = date.GetMonth();

    if (d < Config::SINGLE_DIGIT) // если меньше 10, то первый вывод будет 0
        os << Config::ZERO_FILL;
    os << d << Config::DATE_SEPARATOR; // записываем само число и ставим точку: дд.
    
    if (static_cast<int>(m) < Config::SINGLE_DIGIT) // точно также с месяцем
        os << Config::ZERO_FILL;
    os << static_cast<int>(m) << Config::DATE_SEPARATOR; // 1 в 1
    
    if (y < Config::THREE_DIGITS) // меньше 1000
        os << Config::ZERO_FILL; // ставим 0
    if (y < Config::TWO_DIGITS) // меньше 100 
        os << Config::ZERO_FILL; // ставим 0
    if (y < Config::ONE_DIGIT) // меньше 10
        os << Config::ZERO_FILL; // ставим 0
    os << y; // записываем год

    return os; // выводим всю дату
}

std::istream& operator>>(std::istream& is, CDate& date) // оператор ввода, получаем is как ввод, и дату
{
    unsigned d, m, y; // прописываем переменные
    char dot1, dot2; // переменные разделителя

    if (is >> d >> dot1 >> m >> dot2 >> y && dot1 == Config::DATE_SEPARATOR && dot2 == Config::DATE_SEPARATOR) // проверка на ввод d.m.y
    {
        CDate tmp(d, static_cast<Month>(m), y); // создаем переменную
        if (tmp.IsValid()) // проверка на валидность
            date = tmp; // записываем в дату
        else
            date.m_timestamp = Config::INVALID_TIMESTAMP; // иначе ошибка
    }
    else
    {
        date.m_timestamp = Config::INVALID_TIMESTAMP; // ошибка
    }

    return is; // вывод is
}
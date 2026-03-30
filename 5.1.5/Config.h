#pragma once
#include <string>

namespace Config
{
    // ========== ДИАПАЗОНЫ ДАТ ==========
    const unsigned MIN_YEAR = 1970;
    const unsigned MAX_YEAR = 9999;
    const int MIN_TIMESTAMP = 0;
    const int INVALID_TIMESTAMP = -1;
    
    // ========== ДНИ В МЕСЯЦАХ ==========
    const unsigned DAYS_IN_JANUARY = 31;
    const unsigned DAYS_IN_FEBRUARY_NORMAL = 28;
    const unsigned DAYS_IN_FEBRUARY_LEAP = 29;
    const unsigned DAYS_IN_MARCH = 31;
    const unsigned DAYS_IN_APRIL = 30;
    const unsigned DAYS_IN_MAY = 31;
    const unsigned DAYS_IN_JUNE = 30;
    const unsigned DAYS_IN_JULY = 31;
    const unsigned DAYS_IN_AUGUST = 31;
    const unsigned DAYS_IN_SEPTEMBER = 30;
    const unsigned DAYS_IN_OCTOBER = 31;
    const unsigned DAYS_IN_NOVEMBER = 30;
    const unsigned DAYS_IN_DECEMBER = 31;
    
    // ========== ПАРАМЕТРЫ ВИСОКОСНОГО ГОДА ==========
    const unsigned LEAP_YEAR_DIVISOR_4 = 4;
    const unsigned LEAP_YEAR_DIVISOR_100 = 100;
    const unsigned LEAP_YEAR_DIVISOR_400 = 400;
    const unsigned LEAP_YEAR_EXTRA_DAYS = 366;
    const unsigned NORMAL_YEAR_DAYS = 365;
    
    // ========== ДНИ НЕДЕЛИ ==========
    const int EPOCH_WEEKDAY = 4;  // 01.01.1970 = Thursday
    const int DAYS_IN_WEEK = 7;
    const int WEEKDAY_MIN = 0;
    
    // ========== МЕСЯЦА (для циклов) ==========
    const int FIRST_MONTH = 1;
    const int LAST_MONTH = 12;
    
    // ========== ДНИ (для вычислений) ==========
    const unsigned MIN_DAY = 1;
    const unsigned ZERO_DAY = 0;
    const int DAY_OFFSET = 1;  // для перевода дней в timestamp (day - 1)
    const int TIMESTAMP_TO_DAY_OFFSET = 1;  // для обратного перевода (days + 1)
    
    // ========== НЕВАЛИДНЫЕ ЗНАЧЕНИЯ ==========
    const unsigned INVALID_YEAR = 0;
    const unsigned INVALID_DAY = 0;
    
    // ========== ФОРМАТИРОВАНИЕ ==========
    const int DAY_WIDTH = 2;
    const int MONTH_WIDTH = 2;
    const int YEAR_WIDTH = 4;
    const char DATE_SEPARATOR = '.';
    const int HEX_WIDTH = 6;
    const int ZERO = 0;
    
    // ========== СООБЩЕНИЯ ОБ ОШИБКАХ ==========
    const std::string ERROR_INVALID_YEAR = "ERROR: Year must be between 1970 and 9999\n";
    const std::string ERROR_INVALID_DAY = "ERROR: Day is out of range for the specified month\n";
    const std::string ERROR_INVALID_DATE = "ERROR: Invalid date\n";
    const std::string ERROR_INVALID_TIMESTAMP = "ERROR: Timestamp is negative\n";
    const std::string ERROR_INVALID_INPUT_FORMAT = "ERROR: Invalid input format. Expected DD.MM.YYYY\n";
    const std::string ERROR_INVALID_OPERATOR = "ERROR: Unknown operator\n";
    const std::string ERROR_MISSING_OPERAND = "ERROR: Missing operand\n";
    const std::string ERROR_INVALID_OPERAND = "ERROR: Invalid operand\n";
    const std::string ERROR_DATE_OUT_OF_RANGE = "ERROR: Resulting date is out of valid range\n";
    const std::string ERROR_EMPTY_INPUT = "ERROR: Empty input\n";
    const std::string ERROR_INVALID_NUMBER_FORMAT = "ERROR: Invalid number format\n";
    const std::string ERROR_MISSING_DATE = "ERROR: Missing date operand\n";
    const std::string ERROR_INVALID_INCREMENT = "ERROR: Cannot increment invalid date\n";
    const std::string ERROR_INVALID_DECREMENT = "ERROR: Cannot decrement invalid date\n";
    
    // ========== РЕЗУЛЬТАТЫ ==========
    const std::string RESULT_INVALID = "INVALID";
    const std::string RESULT_TRUE = "true";
    const std::string RESULT_FALSE = "false";
    const std::string RESULT_DAYS_SUFFIX = " days";
    
    // ========== ФОРМАТЫ ВЫВОДА ==========
    const std::string DETAILS_FORMAT = " (Day:{}, Month:{}, Year:{}, WeekDay:{})\n";

        // ========== ФОРМАТИРОВАНИЕ ВЫВОДА ==========
    const int SINGLE_DIGIT = 10;      // для проверки однозначных чисел
    const int THREE_DIGITS = 1000;    // для проверки тысяч
    const int TWO_DIGITS = 100;       // для проверки сотен
    const int ONE_DIGIT = 10;         // для проверки десятков
    
    // ========== ЗАПОЛНИТЕЛИ НУЛЯМИ ==========
    const char ZERO_FILL = '0';
    const int PAD_TO_2_DIGITS = 2;
    const int PAD_TO_4_DIGITS = 4;
}
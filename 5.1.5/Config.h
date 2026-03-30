#pragma once
#include <string>

namespace Config
{
    const unsigned MIN_YEAR = 1970;
    const unsigned MAX_YEAR = 9999;
    const int MIN_TIMESTAMP = 0;
    const int INVALID_TIMESTAMP = -1;
    
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
    
    const unsigned LEAP_YEAR_DIVISOR_4 = 4;
    const unsigned LEAP_YEAR_DIVISOR_100 = 100;
    const unsigned LEAP_YEAR_DIVISOR_400 = 400;
    const unsigned LEAP_YEAR_EXTRA_DAYS = 366;
    const unsigned NORMAL_YEAR_DAYS = 365;
    
    const int EPOCH_WEEKDAY = 4;
    const int DAYS_IN_WEEK = 7;
    const int WEEKDAY_MIN = 0;
    
    const int FIRST_MONTH = 1;
    const int LAST_MONTH = 12;
    
    const unsigned MIN_DAY = 1;
    const unsigned ZERO_DAY = 0;
    const int DAY_OFFSET = 1;
    const int TIMESTAMP_TO_DAY_OFFSET = 1;
    
    const unsigned INVALID_YEAR = 0;
    const unsigned INVALID_DAY = 0;
    const int ZERO = 0;
    
    const int SINGLE_DIGIT = 10;
    const int THREE_DIGITS = 1000;
    const int TWO_DIGITS = 100;
    const int ONE_DIGIT = 10;
    const char ZERO_FILL = '0';
    const char DATE_SEPARATOR = '.';
    const int PAD_TO_2_DIGITS = 2;
    const int PAD_TO_4_DIGITS = 4;
    
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
    
    const std::string RESULT_INVALID = "INVALID";
    const std::string RESULT_TRUE = "true";
    const std::string RESULT_FALSE = "false";
    const std::string RESULT_DAYS_SUFFIX = " days";
    
    const std::string OUTPUT_DAY_PREFIX = " (Day:";
    const std::string OUTPUT_MONTH_PREFIX = ", Month:";
    const std::string OUTPUT_YEAR_PREFIX = ", Year:";
    const std::string OUTPUT_WEEKDAY_PREFIX = ", WeekDay:";
    const std::string OUTPUT_CLOSE_PAREN = ")\n";
    const std::string OUTPUT_SPACE = " ";
    
    const std::string OPERATOR_PLUS = "+";
    const std::string OPERATOR_MINUS = "-";
    const std::string OPERATOR_INCREMENT = "++";
    const std::string OPERATOR_DECREMENT = "--";
    const std::string OPERATOR_PLUS_EQUAL = "+=";
    const std::string OPERATOR_MINUS_EQUAL = "-=";
    const std::string OPERATOR_EQUAL = "==";
    const std::string OPERATOR_NOT_EQUAL = "!=";
    const std::string OPERATOR_LESS = "<";
    const std::string OPERATOR_GREATER = ">";
    const std::string OPERATOR_LESS_EQUAL = "<=";
    const std::string OPERATOR_GREATER_EQUAL = ">=";
}
#include "CDateController.h"
#include "Config.h"
#include <sstream>
#include <cctype>
#include <iomanip>

void PrintDateDetails(const CDate& date, std::ostream& output)
{
    if (!date.IsValid())
    {
        output << Config::RESULT_INVALID << std::endl;
        return;
    }
    
    output << date 
           << Config::OUTPUT_DAY_PREFIX << date.GetDay() 
           << Config::OUTPUT_MONTH_PREFIX << static_cast<int>(date.GetMonth())
           << Config::OUTPUT_YEAR_PREFIX << date.GetYear()
           << Config::OUTPUT_WEEKDAY_PREFIX << static_cast<int>(date.GetWeekDay()) 
           << Config::OUTPUT_CLOSE_PAREN;
}

bool IsNumber(const std::string& str)
{
    if (str.empty()) return false;
    for (char c : str)
    {
        if (!std::isdigit(static_cast<unsigned char>(c)))
            return false;
    }
    return true;
}

void CDateController::ProcessCommands(std::istream& input, std::ostream& output)
{
    std::string firstToken;
    
    while (input >> firstToken)
    {
        bool isNumber = IsNumber(firstToken);
        
        if (isNumber)
        {
            int n = std::stoi(firstToken);
            std::string op;
            CDate date;
            
            if (input >> op >> date && op == Config::OPERATOR_PLUS)
            {
                if (date.IsValid())
                {
                    CDate result = n + date;
                    PrintDateDetails(result, output);
                }
                else
                {
                    output << Config::ERROR_INVALID_DATE;
                    PrintDateDetails(date, output);
                }
            }
            else
            {
                output << Config::ERROR_INVALID_INPUT_FORMAT;
                output << Config::RESULT_INVALID << std::endl;
            }
        }
        else
        {
            std::string dateStr = firstToken;
            
            int dots = Config::ZERO;
            for (char c : dateStr)
                if (c == Config::DATE_SEPARATOR) dots++;
            
            std::string nextToken;
            while (dots < Config::PAD_TO_2_DIGITS && input >> nextToken)
            {
                dateStr += Config::OUTPUT_SPACE + nextToken;
                for (char c : nextToken)
                    if (c == Config::DATE_SEPARATOR) dots++;
                if (dots >= Config::PAD_TO_2_DIGITS) break;
            }
            
            std::istringstream dateIss(dateStr);
            CDate d1;
            dateIss >> d1;
            
            if (!d1.IsValid())
            {
                output << Config::ERROR_INVALID_DATE;
                output << Config::RESULT_INVALID << std::endl;
                
                std::string remaining;
                std::getline(input, remaining);
                continue;
            }
            
            std::string op;
            
            if (!(input >> op))
            {
                PrintDateDetails(d1, output);
                continue;
            }
            
            if (op == Config::OPERATOR_PLUS)
            {
                int n;
                if (input >> n)
                {
                    CDate result = d1 + n;
                    PrintDateDetails(result, output);
                }
                else
                {
                    output << Config::ERROR_MISSING_OPERAND;
                    output << Config::RESULT_INVALID << std::endl;
                }
            }
            else if (op == Config::OPERATOR_MINUS)
            {
                std::streampos pos = input.tellg();
                std::string next;
                
                if (input >> next)
                {
                    if (IsNumber(next))
                    {
                        int n = std::stoi(next);
                        CDate result = d1 - n;
                        PrintDateDetails(result, output);
                    }
                    else
                    {
                        std::istringstream dateIss2(next);
                        CDate d2;
                        dateIss2 >> d2;
                        
                        if (d2.IsValid())
                        {
                            int diff = d1 - d2;
                            output << diff << Config::RESULT_DAYS_SUFFIX << std::endl;
                        }
                        else
                        {
                            output << Config::ERROR_INVALID_DATE;
                            output << Config::RESULT_INVALID << std::endl;
                        }
                    }
                }
                else
                {
                    output << Config::ERROR_MISSING_OPERAND;
                    output << Config::RESULT_INVALID << std::endl;
                }
            }
            else if (op == Config::OPERATOR_INCREMENT)
            {
                CDate result = ++d1;
                PrintDateDetails(result, output);
            }
            else if (op == Config::OPERATOR_DECREMENT)
            {
                CDate result = --d1;
                PrintDateDetails(result, output);
            }
            else if (op == Config::OPERATOR_PLUS_EQUAL)
            {
                int n;
                if (input >> n)
                {
                    d1 += n;
                    PrintDateDetails(d1, output);
                }
                else
                {
                    output << Config::ERROR_MISSING_OPERAND;
                    output << Config::RESULT_INVALID << std::endl;
                }
            }
            else if (op == Config::OPERATOR_MINUS_EQUAL)
            {
                int n;
                if (input >> n)
                {
                    d1 -= n;
                    PrintDateDetails(d1, output);
                }
                else
                {
                    output << Config::ERROR_MISSING_OPERAND;
                    output << Config::RESULT_INVALID << std::endl;
                }
            }
            else if (op == Config::OPERATOR_EQUAL)
            {
                CDate d2;
                if (input >> d2)
                {
                    output << (d1 == d2 ? Config::RESULT_TRUE : Config::RESULT_FALSE) << std::endl;
                }
                else
                {
                    output << Config::ERROR_MISSING_DATE;
                    output << Config::RESULT_INVALID << std::endl;
                }
            }
            else if (op == Config::OPERATOR_NOT_EQUAL)
            {
                CDate d2;
                if (input >> d2)
                {
                    output << (d1 != d2 ? Config::RESULT_TRUE : Config::RESULT_FALSE) << std::endl;
                }
                else
                {
                    output << Config::ERROR_MISSING_DATE;
                    output << Config::RESULT_INVALID << std::endl;
                }
            }
            else if (op == Config::OPERATOR_LESS)
            {
                CDate d2;
                if (input >> d2)
                {
                    output << (d1 < d2 ? Config::RESULT_TRUE : Config::RESULT_FALSE) << std::endl;
                }
                else
                {
                    output << Config::ERROR_MISSING_DATE;
                    output << Config::RESULT_INVALID << std::endl;
                }
            }
            else if (op == Config::OPERATOR_GREATER)
            {
                CDate d2;
                if (input >> d2)
                {
                    output << (d1 > d2 ? Config::RESULT_TRUE : Config::RESULT_FALSE) << std::endl;
                }
                else
                {
                    output << Config::ERROR_MISSING_DATE;
                    output << Config::RESULT_INVALID << std::endl;
                }
            }
            else if (op == Config::OPERATOR_LESS_EQUAL)
            {
                CDate d2;
                if (input >> d2)
                {
                    output << (d1 <= d2 ? Config::RESULT_TRUE : Config::RESULT_FALSE) << std::endl;
                }
                else
                {
                    output << Config::ERROR_MISSING_DATE;
                    output << Config::RESULT_INVALID << std::endl;
                }
            }
            else if (op == Config::OPERATOR_GREATER_EQUAL)
            {
                CDate d2;
                if (input >> d2)
                {
                    output << (d1 >= d2 ? Config::RESULT_TRUE : Config::RESULT_FALSE) << std::endl;
                }
                else
                {
                    output << Config::ERROR_MISSING_DATE;
                    output << Config::RESULT_INVALID << std::endl;
                }
            }
            else
            {
                output << Config::ERROR_INVALID_OPERATOR;
                output << Config::RESULT_INVALID << std::endl;
            }
        }
    }
}
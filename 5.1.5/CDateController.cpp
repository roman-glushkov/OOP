#include "CDateController.h"
#include "Config.h"
#include <sstream>
#include <cctype>

// =====================
// HELPERS
// =====================
bool IsNumber(const std::string& str)
{
    if (str.empty()) return false;
    for (char c : str)
        if (!std::isdigit(static_cast<unsigned char>(c)))
            return false;
    return true;
}

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

// =====================
// NUMBER FIRST (n + date)
// =====================
void HandleNumberFirst(int n, std::istream& input, std::ostream& output)
{
    std::string op;
    if (!(input >> op))
    {
        output << Config::ERROR_MISSING_OPERAND;
        return;
    }

    // ❗ СНАЧАЛА проверка оператора
    if (op != Config::OPERATOR_PLUS)
    {
        output << Config::ERROR_INVALID_OPERATOR;
        return;
    }

    CDate date;
    if (!(input >> date))
    {
        output << Config::ERROR_INVALID_INPUT_FORMAT;
        return;
    }

    if (!date.IsValid())
    {
        output << Config::ERROR_INVALID_DATE;
        return;
    }

    PrintDateDetails(n + date, output);
}

// =====================
// DATE FIRST
// =====================
void HandleDateFirst(const std::string& token, std::istream& input, std::ostream& output)
{
    std::istringstream iss(token);
    CDate d1;
    iss >> d1;

    if (!d1.IsValid())
    {
        output << Config::ERROR_INVALID_DATE;
        return;
    }

    std::string op;
    if (!(input >> op))
    {
        PrintDateDetails(d1, output);
        return;
    }

    // =====================
    // ++ / --
    // =====================
    if (op == Config::OPERATOR_INCREMENT)
    {
        PrintDateDetails(++d1, output);
        return;
    }

    if (op == Config::OPERATOR_DECREMENT)
    {
        PrintDateDetails(--d1, output);
        return;
    }

    // =====================
    // UNKNOWN OPERATOR CHECK (раньше!)
    // =====================
    if (op != Config::OPERATOR_PLUS &&
        op != Config::OPERATOR_MINUS &&
        op != Config::OPERATOR_PLUS_EQUAL &&
        op != Config::OPERATOR_MINUS_EQUAL &&
        op != Config::OPERATOR_EQUAL &&
        op != Config::OPERATOR_NOT_EQUAL &&
        op != Config::OPERATOR_LESS &&
        op != Config::OPERATOR_GREATER &&
        op != Config::OPERATOR_LESS_EQUAL &&
        op != Config::OPERATOR_GREATER_EQUAL)
    {
        output << Config::ERROR_INVALID_OPERATOR;
        return;
    }

    // =====================
    // TRY READ SECOND TOKEN
    // =====================
    std::string nextToken;
    if (!(input >> nextToken))
    {
        output << Config::ERROR_MISSING_OPERAND;
        return;
    }

    // =====================
    // NUMBER OPERATIONS
    // =====================
    if (IsNumber(nextToken))
    {
        int n = std::stoi(nextToken);

        if (op == Config::OPERATOR_PLUS)
            PrintDateDetails(d1 + n, output);
        else if (op == Config::OPERATOR_MINUS)
            PrintDateDetails(d1 - n, output);
        else if (op == Config::OPERATOR_PLUS_EQUAL)
        {
            d1 += n;
            PrintDateDetails(d1, output);
        }
        else if (op == Config::OPERATOR_MINUS_EQUAL)
        {
            d1 -= n;
            PrintDateDetails(d1, output);
        }
        else
        {
            output << Config::ERROR_INVALID_OPERATOR;
        }

        return;
    }

    // =====================
    // SECOND DATE
    // =====================
    CDate d2;
    std::istringstream iss2(nextToken);
    iss2 >> d2;

    if (!d2.IsValid())
    {
        output << Config::ERROR_INVALID_DATE;
        return;
    }

    // =====================
    // DATE OPERATIONS
    // =====================
    if (op == Config::OPERATOR_MINUS)
    {
        output << (d1 - d2) << Config::RESULT_DAYS_SUFFIX << std::endl;
    }
    else if (op == Config::OPERATOR_EQUAL)
        output << (d1 == d2 ? Config::RESULT_TRUE : Config::RESULT_FALSE) << std::endl;
    else if (op == Config::OPERATOR_NOT_EQUAL)
        output << (d1 != d2 ? Config::RESULT_TRUE : Config::RESULT_FALSE) << std::endl;
    else if (op == Config::OPERATOR_LESS)
        output << (d1 < d2 ? Config::RESULT_TRUE : Config::RESULT_FALSE) << std::endl;
    else if (op == Config::OPERATOR_GREATER)
        output << (d1 > d2 ? Config::RESULT_TRUE : Config::RESULT_FALSE) << std::endl;
    else if (op == Config::OPERATOR_LESS_EQUAL)
        output << (d1 <= d2 ? Config::RESULT_TRUE : Config::RESULT_FALSE) << std::endl;
    else if (op == Config::OPERATOR_GREATER_EQUAL)
        output << (d1 >= d2 ? Config::RESULT_TRUE : Config::RESULT_FALSE) << std::endl;
    else
        output << Config::ERROR_INVALID_OPERATOR;
}

// =====================
// MAIN
// =====================
void CDateController::ProcessCommands(std::istream& input, std::ostream& output)
{
    std::string token;

    if (!(input >> token))
        return;

    if (IsNumber(token))
    {
        HandleNumberFirst(std::stoi(token), input, output);
    }
    else
    {
        HandleDateFirst(token, input, output);
    }
}
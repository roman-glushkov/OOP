#include "CDateController.h"
#include <sstream>
#include <cctype>

void PrintDateDetails(const CDate& date, std::ostream& output)
{
    if (!date.IsValid())
    {
        output << "INVALID" << std::endl;
        return;
    }
    
    output << date << " (Day:" << date.GetDay() 
           << ", Month:" << static_cast<int>(date.GetMonth())
           << ", Year:" << date.GetYear()
           << ", WeekDay:" << static_cast<int>(date.GetWeekDay()) << ")" << std::endl;
}

void CDateController::ProcessCommands(std::istream& input, std::ostream& output)
{
    std::string firstToken;
    
    while (input >> firstToken)
    {
        // Проверяем, не число ли это первым (для формата "3 + 28.02.2010")
        bool isNumber = true;
        for (char c : firstToken)
        {
            if (!std::isdigit(c))
            {
                isNumber = false;
                break;
            }
        }
        
        if (isNumber)
        {
            // Формат: число + дата
            int n = std::stoi(firstToken);
            std::string op;
            CDate date;
            
            if (input >> op >> date && op == "+")
            {
                CDate result = n + date;
                PrintDateDetails(result, output);
            }
            else
            {
                output << "INVALID" << std::endl;
            }
        }
        else
        {
            // Формат: дата оператор [операнд]
            // Сначала парсим дату
            std::string dateStr = firstToken;
            
            // Если дата не полная (например, "01.01" без "2010"), дочитываем
            int dots = 0;
            for (char c : dateStr)
                if (c == '.') dots++;
            
            while (dots < 2 && input >> firstToken)
            {
                dateStr += " " + firstToken;
                for (char c : firstToken)
                    if (c == '.') dots++;
            }
            
            std::istringstream dateIss(dateStr);
            CDate d1;
            dateIss >> d1;
            
            // Проверяем, есть ли оператор
            // Сохраняем позицию, чтобы можно было откатиться
            std::streampos pos = input.tellg();
            std::string op;
            
            if (!(input >> op))
            {
                // Нет оператора - выводим дату со всеми геттерами
                PrintDateDetails(d1, output);
                continue;
            }
            
            // Обработка операторов
            if (op == "+")
            {
                int n;
                if (input >> n)
                {
                    CDate result = d1 + n;
                    PrintDateDetails(result, output);
                }
                else
                    output << "INVALID" << std::endl;
            }
            else if (op == "-")
            {
                // Проверяем, что следующий символ
                if (input.peek() == EOF)
                {
                    output << "INVALID" << std::endl;
                }
                else if (std::isdigit(input.peek()))
                {
                    // Вычитание дней: date - N
                    int n;
                    input >> n;
                    CDate result = d1 - n;
                    PrintDateDetails(result, output);
                }
                else
                {
                    // Вычитание дат: date - date
                    CDate d2;
                    if (input >> d2)
                    {
                        int diff = d1 - d2;
                        output << diff << " days" << std::endl;
                    }
                    else
                        output << "INVALID" << std::endl;
                }
            }
            else if (op == "++")
            {
                CDate result = ++d1;
                PrintDateDetails(result, output);
            }
            else if (op == "--")
            {
                CDate result = --d1;
                PrintDateDetails(result, output);
            }
            else if (op == "+=")
            {
                int n;
                if (input >> n)
                {
                    d1 += n;
                    PrintDateDetails(d1, output);
                }
                else
                    output << "INVALID" << std::endl;
            }
            else if (op == "-=")
            {
                int n;
                if (input >> n)
                {
                    d1 -= n;
                    PrintDateDetails(d1, output);
                }
                else
                    output << "INVALID" << std::endl;
            }
            else if (op == "==")
            {
                CDate d2;
                if (input >> d2)
                    output << (d1 == d2 ? "true" : "false") << std::endl;
                else
                    output << "INVALID" << std::endl;
            }
            else if (op == "!=")
            {
                CDate d2;
                if (input >> d2)
                    output << (d1 != d2 ? "true" : "false") << std::endl;
                else
                    output << "INVALID" << std::endl;
            }
            else if (op == "<")
            {
                CDate d2;
                if (input >> d2)
                    output << (d1 < d2 ? "true" : "false") << std::endl;
                else
                    output << "INVALID" << std::endl;
            }
            else if (op == ">")
            {
                CDate d2;
                if (input >> d2)
                    output << (d1 > d2 ? "true" : "false") << std::endl;
                else
                    output << "INVALID" << std::endl;
            }
            else if (op == "<=")
            {
                CDate d2;
                if (input >> d2)
                    output << (d1 <= d2 ? "true" : "false") << std::endl;
                else
                    output << "INVALID" << std::endl;
            }
            else if (op == ">=")
            {
                CDate d2;
                if (input >> d2)
                    output << (d1 >= d2 ? "true" : "false") << std::endl;
                else
                    output << "INVALID" << std::endl;
            }
            else
            {
                output << "INVALID" << std::endl;
            }
        }
    }
}
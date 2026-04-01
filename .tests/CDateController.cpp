#include "CDateController.h"
#include "Config.h"
#include <sstream>
#include <cctype>

// Проверяет, состоит ли строка только из цифр
bool IsNumber(const std::string& str)
{
    if (str.empty()) return false;                     // пустая строка - не число
    
    for (char c : str)                                 // проходим по каждому символу
        if (!std::isdigit(static_cast<unsigned char>(c))) // если не цифра
            return false;                              // то это не число
    
    return true;                                       // все символы цифры
}

// Выводит дату в подробном формате с деталями
void PrintDateDetails(const CDate& date, std::ostream& output)
{
    if (!date.IsValid())                               // если дата невалидна
    {
        output << Config::RESULT_INVALID << std::endl; // выводим "INVALID"
        return;
    }

    // Выводим: дату в формате дд.мм.гггг + детали в скобках
    output << date                                    
           << Config::OUTPUT_DAY_PREFIX << date.GetDay()     
           << Config::OUTPUT_MONTH_PREFIX << static_cast<int>(date.GetMonth()) 
           << Config::OUTPUT_YEAR_PREFIX << date.GetYear()   
           << Config::OUTPUT_WEEKDAY_PREFIX << static_cast<int>(date.GetWeekDay()) 
           << Config::OUTPUT_CLOSE_PAREN;                   
}

// Обрабатывает выражения, начинающиеся с числа
void HandleNumberFirst(int n, std::istream& input, std::ostream& output)
{
    std::string op;
    
    // Читаем оператор (должен быть '+')
    if (!(input >> op))                                 // если оператор не прочитался
    {
        output << Config::ERROR_MISSING_OPERAND;       // "ERROR: Missing operand\n"
        return;
    }

    // Проверяем, что оператор именно '+'
    if (op != Config::OPERATOR_PLUS)                   // если не плюс
    {
        output << Config::ERROR_INVALID_OPERATOR;      // "ERROR: Unknown operator\n"
        return;
    }

    // Читаем дату после оператора
    CDate date;
    if (!(input >> date))                              // если не удалось прочитать дату
    {
        output << Config::ERROR_INVALID_INPUT_FORMAT;  // "ERROR: Invalid input format\n"
        return;
    }

    // Проверяем валидность прочитанной даты
    if (!date.IsValid())                               // если дата невалидна
    {
        output << Config::ERROR_INVALID_DATE;          // "ERROR: Invalid date\n"
        return;
    }

    // Вычисляем и выводим результат: n + date (число + дата)
    PrintDateDetails(n + date, output);                // используем friend operator+(int, CDate)
}

// Обрабатывает выражения, начинающиеся с даты
void HandleDateFirst(const std::string& token, std::istream& input, std::ostream& output)
{
    // ШАГ 1: Парсим первую дату (d1)
    std::istringstream iss(token);                     // создаём поток из токена
    CDate d1;
    iss >> d1;                                         // читаем дату из токена
    
    if (!d1.IsValid())                                 // проверяем валидность
    {
        output << Config::ERROR_INVALID_DATE;
        return;
    }

    // ШАГ 2: Читаем оператор (если есть)
    std::string op;
    if (!(input >> op))                                // если оператора нет (только дата)
    {
        PrintDateDetails(d1, output);                  // просто выводим дату
        return;
    }

    // ШАГ 3: Обрабатываем унарные операторы (++ и --)
    if (op == Config::OPERATOR_INCREMENT)              // если "++"
    {
        PrintDateDetails(++d1, output);                // префиксный инкремент
        return;
    }
    
    if (op == Config::OPERATOR_DECREMENT)              // если "--"
    {
        PrintDateDetails(--d1, output);                // префиксный декремент
        return;
    }

    // ШАГ 4: Проверяем, что оператор поддерживается
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
        output << Config::ERROR_INVALID_OPERATOR;       // неизвестный оператор
        return;
    }

    // ШАГ 5: Читаем второй операнд (токен после оператора)
    std::string nextToken;
    if (!(input >> nextToken))                         // если второго операнда нет
    {
        output << Config::ERROR_MISSING_OPERAND;
        return;
    }

    // ШАГ 6: Определяем тип второго операнда (число или дата)
    if (IsNumber(nextToken))                           // если второй операнд - ЧИСЛО (количество дней)
    {
        int n = std::stoi(nextToken);                  // преобразуем строку в число
        
        // Выбираем нужную операцию
        if (op == Config::OPERATOR_PLUS)               // d1 + n
            PrintDateDetails(d1 + n, output);
        else if (op == Config::OPERATOR_MINUS)         // d1 - n
            PrintDateDetails(d1 - n, output);
        else if (op == Config::OPERATOR_PLUS_EQUAL)    // d1 += n
        {
            d1 += n;
            PrintDateDetails(d1, output);
        }
        else if (op == Config::OPERATOR_MINUS_EQUAL)   // d1 -= n
        {
            d1 -= n;
            PrintDateDetails(d1, output);
        }
        else                                            // оператор не подходит для числа
        {
            output << Config::ERROR_INVALID_OPERATOR;  // (например, d1 == 5 - нельзя)
        }
        return;
    }
    
    // ШАГ 7: Второй операнд - ДАТА (парсим d2)
    CDate d2;
    std::istringstream iss2(nextToken);                // создаём поток из токена
    iss2 >> d2;                                        // читаем дату из токена
    
    if (!d2.IsValid())                                 // проверяем валидность
    {
        output << Config::ERROR_INVALID_DATE;
        return;
    }

    // ШАГ 8: Выполняем бинарные операции с двумя датами

    if (op == Config::OPERATOR_MINUS)                  // d1 - d2 -> разница в днях
    {
        output << (d1 - d2) << Config::RESULT_DAYS_SUFFIX << std::endl; // "2 days\n"
    }
    else if (op == Config::OPERATOR_EQUAL)             // d1 == d2
    {
        output << (d1 == d2 ? Config::RESULT_TRUE : Config::RESULT_FALSE) << std::endl;
    }
    else if (op == Config::OPERATOR_NOT_EQUAL)         // d1 != d2
    {
        output << (d1 != d2 ? Config::RESULT_TRUE : Config::RESULT_FALSE) << std::endl;
    }
    else if (op == Config::OPERATOR_LESS)              // d1 < d2
    {
        output << (d1 < d2 ? Config::RESULT_TRUE : Config::RESULT_FALSE) << std::endl;
    }
    else if (op == Config::OPERATOR_GREATER)           // d1 > d2
    {
        output << (d1 > d2 ? Config::RESULT_TRUE : Config::RESULT_FALSE) << std::endl;
    }
    else if (op == Config::OPERATOR_LESS_EQUAL)        // d1 <= d2
    {
        output << (d1 <= d2 ? Config::RESULT_TRUE : Config::RESULT_FALSE) << std::endl;
    }
    else if (op == Config::OPERATOR_GREATER_EQUAL)     // d1 >= d2
    {
        output << (d1 >= d2 ? Config::RESULT_TRUE : Config::RESULT_FALSE) << std::endl;
    }
    else                                               // любой другой оператор (не должен сюда попасть)
    {
        output << Config::ERROR_INVALID_OPERATOR;
    }
}

// ПУБЛИЧНЫЙ МЕТОД КЛАССА CDateController

// Главная точка входа - обрабатывает команды из входного потока
void CDateController::ProcessCommands(std::istream& input, std::ostream& output)
{
    std::string token;

    // Читаем первый токен (число или дату)
    if (!(input >> token))                             // если нет ввода
        return;                                         // просто выходим (ничего не выводим)

    // Определяем тип первого токена и передаём управление соответствующему обработчику
    if (IsNumber(token))                               // первый токен - ЧИСЛО
    {
        HandleNumberFirst(std::stoi(token), input, output); // формат: "N + date"
    }
    else                                               // первый токен - ДАТА (или что-то ещё)
    {
        HandleDateFirst(token, input, output);         // все остальные форматы
    }
}
#include "CMyListController.h"
#include "CMyList.h"
#include <string>
#include <sstream>

static void PrintMenu(std::ostream& output)
{
    output << "\n=== CMyList Demo ===\n";
    output << "Commands:\n";
    output << "  sb <str>      - PushBack string\n";
    output << "  sf <str>      - PushFront string\n";
    output << "  ib <idx> <str> - Insert string at position\n";
    output << "  db <idx>      - Delete string at position\n";
    output << "  nb <num>      - PushBack number\n";
    output << "  nf <num>      - PushFront number\n";
    output << "  in <idx> <num> - Insert number at position\n";
    output << "  dn <idx>      - Delete number at position\n";
    output << "  ps            - Print strings (forward)\n";
    output << "  rs            - Print strings (reverse)\n";
    output << "  pn            - Print numbers (forward)\n";
    output << "  rn            - Print numbers (reverse)\n";
    output << "  size          - Show sizes\n";
    output << "  clear         - Clear both lists\n";
    output << "  q             - Quit\n";
}

static void PrintStringForward(CMyList<std::string>& list, std::ostream& output)
{
    if (list.Empty())
    {
        output << "(empty)\n";
        return;
    }
    for (auto it = list.begin(); it != list.end(); ++it)
        output << *it << " ";
    output << "\n";
}

static void PrintStringReverse(CMyList<std::string>& list, std::ostream& output)
{
    if (list.Empty())
    {
        output << "(empty)\n";
        return;
    }
    
    // Начинаем с последнего элемента
    auto it = list.begin();
    auto end = list.end();
    
    // Идём в конец
    while (it != end)
        ++it;
    
    // Откатываемся на один шаг назад (теперь it указывает на последний элемент)
    --it;
    
    // Печатаем в обратном порядке
    while (true)
    {
        output << *it << " ";
        if (it == list.begin())
            break;
        --it;
    }
    output << "\n";
}

static void PrintNumberForward(CMyList<int>& list, std::ostream& output)
{
    if (list.Empty())
    {
        output << "(empty)\n";
        return;
    }
    for (auto it = list.begin(); it != list.end(); ++it)
        output << *it << " ";
    output << "\n";
}

static void PrintNumberReverse(CMyList<int>& list, std::ostream& output)
{
    if (list.Empty())
    {
        output << "(empty)\n";
        return;
    }
    
    // Начинаем с последнего элемента
    auto it = list.begin();
    auto end = list.end();
    
    // Идём в конец
    while (it != end)
        ++it;
    
    // Откатываемся на один шаг назад (теперь it указывает на последний элемент)
    --it;
    
    // Печатаем в обратном порядке
    while (true)
    {
        output << *it << " ";
        if (it == list.begin())
            break;
        --it;
    }
    output << "\n";
}

static int ParseIndex(const std::string& str, std::ostream& output)
{
    try
    {
        return std::stoi(str);
    }
    catch (...)
    {
        output << "Invalid index\n";
        return -1;
    }
}

void CMyListController::ProcessCommands(std::istream& input, std::ostream& output)
{
    CMyList<std::string> stringList;
    CMyList<int> numberList;
    std::string command;
    
    PrintMenu(output);
    
    while (input >> command)
    {
        if (command == "sb")
        {
            std::string value;
            input >> value;
            stringList.PushBack(value);
            output << "PushBack string: " << value << "\n";
        }
        else if (command == "sf")
        {
            std::string value;
            input >> value;
            stringList.PushFront(value);
            output << "PushFront string: " << value << "\n";
        }
        else if (command == "ib")
        {
            std::string idxStr, value;
            input >> idxStr >> value;
            int idx = ParseIndex(idxStr, output);
            if (idx >= 0)
            {
                try
                {
                    auto it = stringList.begin();
                    for (int i = 0; i < idx && it != stringList.end(); ++i, ++it);
                    stringList.insert(it, value);
                    output << "Inserted at " << idx << ": " << value << "\n";
                }
                catch (const std::exception& e)
                {
                    output << "Insert failed: " << e.what() << "\n";
                }
            }
        }
        else if (command == "db")
        {
            std::string idxStr;
            input >> idxStr;
            int idx = ParseIndex(idxStr, output);
            if (idx >= 0)
            {
                try
                {
                    auto it = stringList.begin();
                    for (int i = 0; i < idx && it != stringList.end(); ++i, ++it);
                    if (it != stringList.end())
                    {
                        stringList.erase(it);
                        output << "Deleted at position " << idx << "\n";
                    }
                    else
                    {
                        output << "Position out of range\n";
                    }
                }
                catch (const std::exception& e)
                {
                    output << "Delete failed: " << e.what() << "\n";
                }
            }
        }
        else if (command == "nb")
        {
            int value;
            input >> value;
            numberList.PushBack(value);
            output << "PushBack number: " << value << "\n";
        }
        else if (command == "nf")
        {
            int value;
            input >> value;
            numberList.PushFront(value);
            output << "PushFront number: " << value << "\n";
        }
        else if (command == "in")
        {
            std::string idxStr;
            int value;
            input >> idxStr >> value;
            int idx = ParseIndex(idxStr, output);
            if (idx >= 0)
            {
                try
                {
                    auto it = numberList.begin();
                    for (int i = 0; i < idx && it != numberList.end(); ++i, ++it);
                    numberList.insert(it, value);
                    output << "Inserted at " << idx << ": " << value << "\n";
                }
                catch (const std::exception& e)
                {
                    output << "Insert failed: " << e.what() << "\n";
                }
            }
        }
        else if (command == "dn")
        {
            std::string idxStr;
            input >> idxStr;
            int idx = ParseIndex(idxStr, output);
            if (idx >= 0)
            {
                try
                {
                    auto it = numberList.begin();
                    for (int i = 0; i < idx && it != numberList.end(); ++i, ++it);
                    if (it != numberList.end())
                    {
                        numberList.erase(it);
                        output << "Deleted at position " << idx << "\n";
                    }
                    else
                    {
                        output << "Position out of range\n";
                    }
                }
                catch (const std::exception& e)
                {
                    output << "Delete failed: " << e.what() << "\n";
                }
            }
        }
        else if (command == "ps")
        {
            output << "Strings (forward): ";
            PrintStringForward(stringList, output);
        }
        else if (command == "rs")
        {
            output << "Strings (reverse): ";
            PrintStringReverse(stringList, output);
        }
        else if (command == "pn")
        {
            output << "Numbers (forward): ";
            PrintNumberForward(numberList, output);
        }
        else if (command == "rn")
        {
            output << "Numbers (reverse): ";
            PrintNumberReverse(numberList, output);
        }
        else if (command == "size")
        {
            output << "Strings count: " << stringList.Size() << "\n";
            output << "Numbers count: " << numberList.Size() << "\n";
        }
        else if (command == "clear")
        {
            stringList.Clear();
            numberList.Clear();
            output << "Both lists cleared\n";
        }
        else if (command == "q")
        {
            output << "Goodbye!\n";
            break;
        }
        else
        {
            output << "Unknown command: " << command << ". Type 'q' to quit\n";
        }
    }
}
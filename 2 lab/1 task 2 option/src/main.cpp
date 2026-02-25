#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

const int OUTPUT_PRECISION = 3; 
const std::string ERROR_INVALID_DATA = "ERROR";

std::vector<double> ReadNumbers()
{
    std::vector<double> numbers;
    double num;
    
    while (std::cin >> num)
    {
        numbers.push_back(num);
    }
    
    return numbers;
}

std::vector<double> ProcessNumbers(const std::vector<double>& numbers)
{
    if (numbers.empty())
    {
        return numbers;
    }
    
    double minValue = *std::min_element(numbers.begin(), numbers.end());
    
    std::vector<double> result;
    result.reserve(numbers.size());
    
    for (double value : numbers)
    {
        result.push_back(value * minValue);
    }
    
    return result;
}

void PrintSortedNumbers(const std::vector<double>& numbers)
{
    if (numbers.empty())
    {
        return;
    }
    
    std::vector<double> sorted = numbers;
    std::sort(sorted.begin(), sorted.end());
    
    std::cout << std::fixed << std::setprecision(OUTPUT_PRECISION);
    
    for (size_t i = 0; i < sorted.size(); ++i)
    {
        if (i > 0)
        {
            std::cout << " ";
        }
        std::cout << sorted[i];
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<double> numbers = ReadNumbers();
    
    if (!std::cin.eof())
    {
        std::cout << ERROR_INVALID_DATA << std::endl;
        return 0;
    }
    
    std::vector<double> result = ProcessNumbers(numbers);
    PrintSortedNumbers(result);
    
    return 0;
}
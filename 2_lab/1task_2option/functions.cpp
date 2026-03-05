#include "functions.h"
#include <algorithm>
#include <iomanip>
#include <iterator>

const int OUTPUT_PRECISION = 3;

std::vector<double> ReadNumbers(std::istream& in, bool& isValid)
{
    std::vector<double> numbers;

    std::copy(
        std::istream_iterator<double>(in),
        std::istream_iterator<double>(),
        std::back_inserter(numbers)
    );

    if (!in.eof())
    {
        isValid = false;
        return {};
    }

    isValid = true;
    return numbers;
}

std::vector<double> ProcessNumbers(const std::vector<double>& numbers)
{
    if (numbers.empty())
    {
        return {};
    }

    double minValue = *std::min_element(numbers.begin(), numbers.end());

    std::vector<double> result(numbers.size());

    std::transform(
        numbers.begin(),
        numbers.end(),
        result.begin(),
        [minValue](double value)
        {
            return value * minValue;
        }
    );

    return result;
}

void PrintSortedNumbers(const std::vector<double>& numbers, std::ostream& out)
{
    if (numbers.empty())
    {
        return;
    }

    std::vector<double> sorted(numbers);

    std::sort(sorted.begin(), sorted.end());

    out << std::fixed << std::setprecision(OUTPUT_PRECISION);

    std::copy(
        sorted.begin(),
        sorted.end() - 1,
        std::ostream_iterator<double>(out, " ")
    );
    out << sorted.back();
    out << std::endl;
}
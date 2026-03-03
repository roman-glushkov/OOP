#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <iterator>
#include <numeric>

const int OUTPUT_PRECISION = 3;
const std::string ERROR_INVALID_DATA = "ERROR";

int main() 
{
  std::vector < double > numbers;

  std::copy(std::istream_iterator < double > (std::cin), std::istream_iterator < double > (), std::back_inserter(numbers));

  if (!std::cin.eof()) 
  {
    std::cout << ERROR_INVALID_DATA << std::endl;
    return 1;
  }

  if (!numbers.empty()) 
  {
    double minValue = * std::min_element(numbers.begin(), numbers.end());
    
    std::transform(numbers.begin(), numbers.end(), numbers.begin(), [minValue](double v) 
    { 
        return v * minValue;
      });

    std::sort(numbers.begin(), numbers.end());

    std::cout << std::fixed << std::setprecision(OUTPUT_PRECISION);

    std::copy(numbers.begin(), numbers.end(), std::ostream_iterator < double > (std::cout, " "));
    
    std::cout << std::endl;
  }

  return 0;
}
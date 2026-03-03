#pragma once
#include <vector>
#include <istream>
#include <ostream>

std::vector<double> ReadNumbers(std::istream& in, bool& isValid);
std::vector<double> ProcessNumbers(const std::vector<double>& numbers);
void PrintSortedNumbers(const std::vector<double>& numbers, std::ostream& out);
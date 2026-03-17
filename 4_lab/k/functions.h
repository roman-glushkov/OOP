#pragma once
#include <vector>
#include <string>
#include <istream>

std::vector<std::string> ReadLines(std::istream& in, bool& isValid);
std::string HtmlDecode(std::string const& html);
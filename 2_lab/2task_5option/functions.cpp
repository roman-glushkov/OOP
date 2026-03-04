#include "functions.h"

std::vector<std::string> ReadLines(std::istream& in, bool& isValid)
{
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(in, line))
    {
        lines.push_back(line);
    }

    if (!in.eof())
    {
        isValid = false;
        return {};
    }

    isValid = true;
    return lines;
}

std::string HtmlDecode(std::string const& html)
{
    std::string result;
    result.reserve(html.size());

    for (size_t i = 0; i < html.size();)
    {
        if (html[i] == '&')
        {
            if (html.compare(i, 6, "&quot;") == 0)
            {
                result.push_back('"');
                i += 6;
            }
            else if (html.compare(i, 6, "&apos;") == 0)
            {
                result.push_back('\'');
                i += 6;
            }
            else if (html.compare(i, 4, "&lt;") == 0)
            {
                result.push_back('<');
                i += 4;
            }
            else if (html.compare(i, 4, "&gt;") == 0)
            {
                result.push_back('>');
                i += 4;
            }
            else if (html.compare(i, 5, "&amp;") == 0)
            {
                result.push_back('&');
                i += 5;
            }
            else
            {
                result.push_back(html[i]);
                ++i;
            }
        }
        else
        {
            result.push_back(html[i]);
            ++i;
        }
    }

    return result;
}
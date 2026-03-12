#include "functions.h"
#include <map>

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

std::string HtmlDecode(const std::string& html)
{
    static const std::map<std::string, char> entities =
    {
        {"&quot;", '"'},
        {"&apos;", '\''},
        {"&lt;", '<'},
        {"&gt;", '>'},
        {"&amp;", '&'}
    };

    std::string result;
    result.reserve(html.size());

    for (size_t i = 0; i < html.size();)
    {
        bool replaced = false;

        if (html[i] == '&')
        {
            for (const auto& [key, value] : entities)
            {
                if (html.compare(i, key.size(), key) == 0)
                {
                    result += value;
                    i += key.size();
                    replaced = true;
                    break;
                }
            }
        }

        if (!replaced)
            result += html[i++];
    }

    return result;
}
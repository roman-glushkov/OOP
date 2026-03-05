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

std::string HtmlDecode(const std::string& html)
{
    std::string result = html;

    const std::map<std::string, std::string> entities =
    {
        {"&quot;", "\""},
        {"&apos;", "'"},
        {"&lt;", "<"},
        {"&gt;", ">"},
        {"&amp;", "&"}
    };

    for (const auto& entity : entities)
    {
        size_t pos = 0;

        while ((pos = result.find(entity.first, pos)) != std::string::npos)
        {
            result.replace(pos, entity.first.length(), entity.second);
        }
    }

    return result;
}
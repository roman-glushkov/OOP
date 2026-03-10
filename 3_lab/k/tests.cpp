#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "functions.h"
#include <sstream>

TEST_CASE("ReadLines reads valid input")
{
    std::istringstream input("line1\nline2\nline3");
    bool isValid = true;

    auto result = ReadLines(input, isValid);

    REQUIRE(isValid);
    REQUIRE(result.size() == 3);
    CHECK(result[0] == "line1");
    CHECK(result[1] == "line2");
    CHECK(result[2] == "line3");
}

TEST_CASE("ReadLines handles empty input")
{
    std::istringstream input("");
    bool isValid = true;

    auto result = ReadLines(input, isValid);

    REQUIRE(isValid);
    CHECK(result.empty());
}

TEST_CASE("HtmlDecode decodes basic entities")
{
    CHECK(HtmlDecode("&quot;") == "\"");
    CHECK(HtmlDecode("&apos;") == "'");
    CHECK(HtmlDecode("&lt;") == "<");
    CHECK(HtmlDecode("&gt;") == ">");
    CHECK(HtmlDecode("&amp;") == "&");
}

TEST_CASE("HtmlDecode decodes mixed string")
{
    std::string input = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
    std::string expected = "Cat <says> \"Meow\". M&M's";

    CHECK(HtmlDecode(input) == expected);
}

TEST_CASE("HtmlDecode leaves unknown entity unchanged")
{
    CHECK(HtmlDecode("&unknown;") == "&unknown;");
}

TEST_CASE("HtmlDecode works for multiple lines")
{
    std::vector<std::string> input =
    {
        "Cat &lt;says&gt;",
        "M&amp;M&apos;s",
        "&quot;Hello&quot;"
    };

    std::vector<std::string> expected =
    {
        "Cat <says>",
        "M&M's",
        "\"Hello\""
    };

    std::vector<std::string> result;

    for (const auto& line : input)
    {
        result.push_back(HtmlDecode(line));
    }

    CHECK(result == expected);
}
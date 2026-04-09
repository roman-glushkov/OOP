#define CONFIG_H
#include <numbers>
#include <float.h>


namespace Config
{
    const double EPSILON = DBL_EPSILON;
    const double PI = std::numbers::pi;
    const double TWO_PI = 2.0 * PI;
    const double FOUR_PI = 4.0 * PI;

    const double NEGATIVE_ZERO = -0.0;
    const double POSITIVE_ZERO = 0.0;
    const int ZERO = 0;
    const int ONE = 1;
    const int TWO = 2;
    const int THREE = 3;
    const int FOUR = 4;
    const double HALF = 0.5;
    const double ONE_THIRD = 1.0 / 3.0;
    const double TWO_THIRDS = 2.0 / 3.0;

    const int DIV_BY_2 = 2;
    const int DIV_BY_3 = 3;
    const int DIV_BY_27 = 27;

    const double ROUNDING_EPSILON = 1e-9;
    const double ROUND_THRESHOLD = 1e-9;

    const char* const ERROR_COEFFICIENT_ZERO = "Coefficient at x^3 cannot be zero";
    const char* const ERROR_PREFIX = "Error: ";
    const char SPACE = ' ';
    const char NEWLINE = '\n';
}

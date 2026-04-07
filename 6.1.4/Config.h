#define CONFIG_H

namespace Config
{
    const double EPSILON = 1e-12;
    const double ROUNDING_EPSILON = 1e-9;

    const double TWO_PI = 2.0 * 3.14159265358979323846;
    const double FOUR_PI = 4.0 * 3.14159265358979323846;

    const double ROUND_THRESHOLD = 1e-9;

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

    const char* const ERROR_COEFFICIENT_ZERO = "Coefficient at x^3 cannot be zero";
    const char* const ERROR_PREFIX = "Error: ";
    const char SPACE = ' ';
    const char NEWLINE = '\n';
}

#pragma once

namespace Config
{
    // File settings
    const char* const DATABASE_FILE = "athletes.txt";
    const char DELIMITER = '|';

    // Error messages
    const char* const ERROR_EMPTY_ARRAY = "Error: array is empty";
    const char* const ERROR_FILE_NOT_OPEN = "Error: cannot open database file";

    // Output messages
    const char* const MSG_SEARCH_HEIGHT = "Searching athlete with maximum height...";
    const char* const MSG_SEARCH_WEIGHT = "Searching athlete with maximum weight...";

    // Output formatting
    const char* const UNIT_HEIGHT = "m";
    const char* const UNIT_WEIGHT = "kg";
    const char* const SEPARATOR = " | ";

    // Parsing
    const int IGNORE_COUNT = 1;
}
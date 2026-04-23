#pragma once

namespace Config
{
    const char* const DATABASE_FILE = "athletes.txt";
    const char DELIMITER = '|';
    const char* const ERROR_PREFIX = "Error: ";
    const char* const ERROR_EMPTY_ARRAY = "Error: array is empty";
    const char* const ERROR_FILE_NOT_OPEN = "Error: cannot open database file";
    const char* const ERROR_LINE_PREFIX = "Line ";
    const char* const ERROR_LINE_SEPARATOR = ": ";
    const char* const ERROR_HEIGHT_POSITIVE = "Height must be positive";
    const char* const ERROR_WEIGHT_POSITIVE = "Weight must be positive";
    const char* const MSG_SEARCH_HEIGHT = "Searching athlete with maximum height...";
    const char* const MSG_SEARCH_WEIGHT = "Searching athlete with maximum weight...";
    const char* const UNIT_HEIGHT = "m";
    const char* const UNIT_WEIGHT = "kg";
    const char* const SEPARATOR = " | ";
    const int IGNORE_COUNT = 1;
}
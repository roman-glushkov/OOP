#pragma once

#include "Shape.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <istream>
#include <ostream>
#include <sstream>

class ShapeController
{
public:
    ShapeController(std::istream& input, std::ostream& output);
    void ProcessCommands();

private:
    using Command = std::function<void(std::istringstream&)>;

    std::istream& m_input;
    std::ostream& m_output;

    std::vector<std::shared_ptr<Shape>> m_shapes;

    std::map<std::string, Command> m_commands;

    bool isValidColor(const std::string& color) const;
    std::shared_ptr<Shape> parseShape(const std::string& line);
    std::shared_ptr<Shape> findMaxArea() const;
    std::shared_ptr<Shape> findMinPerimeter() const;
    void printShapeInfo(const std::shared_ptr<Shape>& shape, const std::string& title) const;
    void printResults() const;

    // Command handlers
    void HandleShapeInput(std::istringstream& args);
    void HandlePrintResults(std::istringstream& args);

    // Static constants
public:
    // Error messages
    static constexpr const char* ERROR_PREFIX = "ERROR: ";
    static constexpr const char* ERROR_INVALID_FORMAT = "invalid input format\n";
    static constexpr const char* ERROR_UNKNOWN_TYPE = "unknown shape type\n";
    static constexpr const char* ERROR_INVALID_COLOR = "invalid color\n";
    static constexpr const char* ERROR_EXTRA_DATA = "extra data in input\n";
    static constexpr const char* ERROR_INVALID_RADIUS = "radius must be positive\n";
    static constexpr const char* ERROR_EMPTY_INPUT = "empty input\n";

    // Shape types
    static constexpr const char* SHAPE_RECTANGLE = "rectangle";
    static constexpr const char* SHAPE_SQUARE = "square";
    static constexpr const char* SHAPE_RHOMBUS = "rhombus";
    static constexpr const char* SHAPE_PARALLELOGRAM = "parallelogram";
    static constexpr const char* SHAPE_TRAPEZOID = "trapezoid";
    static constexpr const char* SHAPE_CIRCLE = "circle";
    static constexpr const char* SHAPE_TRIANGLE = "triangle";
    static constexpr const char* SHAPE_LINE = "line";

    // UI messages
    static constexpr const char* PROMPT_ENTER_SHAPES = "Enter shapes (Enter 'done' to finish):\n";
    static constexpr const char* PROMPT_CONTINUE = "Enter next shape or 'done' to finish:\n";
    static constexpr const char* MSG_ADDED_PREFIX = "Added: ";
    static constexpr const char* MSG_NO_SHAPES = "\nNo shapes entered.\n";
    static constexpr const char* MSG_TOTAL_SHAPES_PREFIX = "\nTotal shapes: ";
    static constexpr const char* MSG_SEPARATOR = "==================================================";

    // Output format strings
    static constexpr const char* OUTPUT_TITLE_PREFIX = "\n=== ";
    static constexpr const char* OUTPUT_TITLE_SUFFIX = " ===\n";
    static constexpr const char* OUTPUT_AREA = "Area: ";
    static constexpr const char* OUTPUT_PERIMETER = "Perimeter: ";
    static constexpr const char* OUTPUT_OUTLINE_COLOR = "Outline color: #";
    static constexpr const char* OUTPUT_FILL_COLOR = "Fill color: #";
    static constexpr const char* OUTPUT_FILL_COLOR_NONE = "none";

    // Special titles
    static constexpr const char* TITLE_MAX_AREA = "SHAPE WITH MAXIMUM AREA";
    static constexpr const char* TITLE_MIN_PERIMETER = "SHAPE WITH MINIMUM PERIMETER";

    // Commands
    static constexpr const char* CMD_DONE = "done";
};
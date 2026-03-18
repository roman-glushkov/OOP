#pragma once

#include "Shape.h"
#include <string>
#include <vector>
#include <memory>

const std::string ERROR_PREFIX = "ERROR: ";
const std::string ERROR_INVALID_FORMAT = "invalid input format\n";
const std::string ERROR_UNKNOWN_TYPE = "unknown shape type\n";
const std::string ERROR_INVALID_COLOR = "invalid color\n";
const std::string ERROR_EXTRA_DATA = "extra data in input\n";
const std::string ERROR_INVALID_RADIUS = "radius must be positive\n";
const std::string ERROR_EMPTY_INPUT = "empty input\n";

const std::string SHAPE_RECTANGLE = "rectangle";
const std::string SHAPE_SQUARE = "square";
const std::string SHAPE_RHOMBUS = "rhombus";
const std::string SHAPE_PARALLELOGRAM = "parallelogram";
const std::string SHAPE_TRAPEZOID = "trapezoid";
const std::string SHAPE_CIRCLE = "circle";
const std::string SHAPE_TRIANGLE = "triangle";
const std::string SHAPE_LINE = "line";

const std::string PROMPT_ENTER_SHAPES = "Enter shapes (Ctrl+Z or Ctrl+D to end):\n";
const std::string MSG_ADDED_PREFIX = "Added: ";
const std::string MSG_NO_SHAPES = "\nNo shapes entered.\n";
const std::string MSG_TOTAL_SHAPES = "\n" + std::string(50, '=') + "\nTotal shapes: ";
const std::string MSG_SEPARATOR = "\n" + std::string(50, '=') + "\n";

const std::string OUTPUT_TITLE_PREFIX = "\n=== ";
const std::string OUTPUT_TITLE_SUFFIX = " ===\n";
const std::string OUTPUT_AREA = "Area: ";
const std::string OUTPUT_PERIMETER = "Perimeter: ";
const std::string OUTPUT_OUTLINE_COLOR = "Outline color: #";
const std::string OUTPUT_FILL_COLOR = "Fill color: #";
const std::string OUTPUT_FILL_COLOR_NONE = "none";
const std::string NEWLINE = "\n";

const std::string TITLE_MAX_AREA = "SHAPE WITH MAXIMUM AREA";
const std::string TITLE_MIN_PERIMETER = "SHAPE WITH MINIMUM PERIMETER";

bool isValidColor(const std::string& color);
std::shared_ptr<Shape> parseShape(const std::string& line);
std::shared_ptr<Shape> findMaxArea(const std::vector<std::shared_ptr<Shape>>& shapes);
std::shared_ptr<Shape> findMinPerimeter(const std::vector<std::shared_ptr<Shape>>& shapes);
void printShapeInfo(const std::shared_ptr<Shape>& shape, const std::string& title);
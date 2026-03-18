#include "ShapeController.h"
#include <algorithm>
#include <cctype>
#include <iomanip>

ShapeController::ShapeController(std::istream& input, std::ostream& output)
    : m_input(input)
    , m_output(output)
{
    m_commands[CMD_DONE] = [this](std::istringstream& args) { HandlePrintResults(args); };
}

void ShapeController::ProcessCommands()
{
    m_output << PROMPT_ENTER_SHAPES;

    std::string line;
    while (std::getline(m_input, line))
    {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string command;
        iss >> command;

        std::transform(command.begin(), command.end(), command.begin(), ::tolower);

        auto it = m_commands.find(command);
        if (it != m_commands.end())
        {
            it->second(iss);
            return; // Exit after processing 'done'
        }
        else
        {
            // Treat as shape input
            iss.str(line);
            iss.clear();
            HandleShapeInput(iss);
        }

        m_output << PROMPT_CONTINUE;
    }
}

bool ShapeController::isValidColor(const std::string& color) const
{
    if (color.length() != 6) return false;
    for (char c : color) {
        if (!std::isxdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

std::shared_ptr<Shape> ShapeController::parseShape(const std::string& line)
{
    std::istringstream iss(line);
    std::string type;

    if (!(iss >> type)) {
        m_output << ERROR_PREFIX << ERROR_EMPTY_INPUT;
        return nullptr;
    }

    std::transform(type.begin(), type.end(), type.begin(), ::tolower);

    if (type == SHAPE_RECTANGLE || type == SHAPE_SQUARE || type == SHAPE_RHOMBUS ||
        type == SHAPE_PARALLELOGRAM || type == SHAPE_TRAPEZOID) {

        double x1, y1, x2, y2, x3, y3, x4, y4;
        std::string outline, fill;

        if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> outline >> fill)) {
            m_output << ERROR_PREFIX << ERROR_INVALID_FORMAT;
            return nullptr;
        }

        if (!isValidColor(outline) || !isValidColor(fill)) {
            m_output << ERROR_PREFIX << ERROR_INVALID_COLOR;
            return nullptr;
        }

        std::string extra;
        if (iss >> extra) {
            m_output << ERROR_PREFIX << ERROR_EXTRA_DATA;
            return nullptr;
        }

        QuadrilateralType qType;
        if (type == SHAPE_RECTANGLE) qType = QuadrilateralType::Rectangle;
        else if (type == SHAPE_SQUARE) qType = QuadrilateralType::Square;
        else if (type == SHAPE_RHOMBUS) qType = QuadrilateralType::Rhombus;
        else if (type == SHAPE_PARALLELOGRAM) qType = QuadrilateralType::Parallelogram;
        else qType = QuadrilateralType::Trapezoid;

        return std::make_shared<Quadrilateral>(
            Point(x1, y1), Point(x2, y2), Point(x3, y3), Point(x4, y4),
            qType, outline, fill
        );
    }
    else if (type == SHAPE_CIRCLE) {
        double x, y, radius;
        std::string outline, fill;

        if (!(iss >> x >> y >> radius >> outline >> fill)) {
            m_output << ERROR_PREFIX << ERROR_INVALID_FORMAT;
            return nullptr;
        }

        if (radius <= 0) {
            m_output << ERROR_PREFIX << ERROR_INVALID_RADIUS;
            return nullptr;
        }

        if (!isValidColor(outline) || !isValidColor(fill)) {
            m_output << ERROR_PREFIX << ERROR_INVALID_COLOR;
            return nullptr;
        }

        std::string extra;
        if (iss >> extra) {
            m_output << ERROR_PREFIX << ERROR_EXTRA_DATA;
            return nullptr;
        }

        return std::make_shared<Circle>(Point(x, y), radius, outline, fill);
    }
    else if (type == SHAPE_TRIANGLE) {
        double x1, y1, x2, y2, x3, y3;
        std::string outline, fill;

        if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> outline >> fill)) {
            m_output << ERROR_PREFIX << ERROR_INVALID_FORMAT;
            return nullptr;
        }

        if (!isValidColor(outline) || !isValidColor(fill)) {
            m_output << ERROR_PREFIX << ERROR_INVALID_COLOR;
            return nullptr;
        }

        std::string extra;
        if (iss >> extra) {
            m_output << ERROR_PREFIX << ERROR_EXTRA_DATA;
            return nullptr;
        }

        return std::make_shared<Triangle>(
            Point(x1, y1), Point(x2, y2), Point(x3, y3),
            outline, fill
        );
    }
    else if (type == SHAPE_LINE) {
        double x1, y1, x2, y2;
        std::string outline;

        if (!(iss >> x1 >> y1 >> x2 >> y2 >> outline)) {
            m_output << ERROR_PREFIX << ERROR_INVALID_FORMAT;
            return nullptr;
        }

        if (!isValidColor(outline)) {
            m_output << ERROR_PREFIX << ERROR_INVALID_COLOR;
            return nullptr;
        }

        std::string extra;
        if (iss >> extra) {
            m_output << ERROR_PREFIX << ERROR_EXTRA_DATA;
            return nullptr;
        }

        return std::make_shared<Line>(
            Point(x1, y1), Point(x2, y2),
            outline
        );
    }

    m_output << ERROR_PREFIX << ERROR_UNKNOWN_TYPE;
    return nullptr;
}

void ShapeController::HandleShapeInput(std::istringstream& args)
{
    std::string line = args.str();
    auto shape = parseShape(line);

    if (shape) {
        m_shapes.push_back(shape);
        m_output << MSG_ADDED_PREFIX << shape->ToString() << "\n";
    }
}

void ShapeController::HandlePrintResults(std::istringstream& args)
{
    printResults();
}

std::shared_ptr<Shape> ShapeController::findMaxArea() const
{
    if (m_shapes.empty()) return nullptr;

    auto maxShape = m_shapes[0];
    for (const auto& shape : m_shapes) {
        if (shape->Area() > maxShape->Area()) {
            maxShape = shape;
        }
    }
    return maxShape;
}

std::shared_ptr<Shape> ShapeController::findMinPerimeter() const
{
    if (m_shapes.empty()) return nullptr;

    auto minShape = m_shapes[0];
    for (const auto& shape : m_shapes) {
        if (shape->Perimeter() < minShape->Perimeter()) {
            minShape = shape;
        }
    }
    return minShape;
}

void ShapeController::printShapeInfo(const std::shared_ptr<Shape>& shape, const std::string& title) const
{
    if (!shape) return;

    m_output << OUTPUT_TITLE_PREFIX << title << OUTPUT_TITLE_SUFFIX;
    m_output << shape->ToString() << "\n";
    m_output << OUTPUT_AREA << std::fixed << std::setprecision(2) << shape->Area() << "\n";
    m_output << OUTPUT_PERIMETER << std::fixed << std::setprecision(2) << shape->Perimeter() << "\n";
    m_output << OUTPUT_OUTLINE_COLOR << shape->outlineColor << "\n";

    if (shape->fillColor != OUTPUT_FILL_COLOR_NONE) {
        m_output << OUTPUT_FILL_COLOR << shape->fillColor << "\n";
    }
}

void ShapeController::printResults() const
{
    if (m_shapes.empty()) {
        m_output << MSG_NO_SHAPES;
        return;
    }

    m_output << "\n" << MSG_SEPARATOR << "\n";
    m_output << MSG_TOTAL_SHAPES_PREFIX << m_shapes.size() << "\n";

    auto maxAreaShape = findMaxArea();
    auto minPerimeterShape = findMinPerimeter();

    printShapeInfo(maxAreaShape, TITLE_MAX_AREA);
    printShapeInfo(minPerimeterShape, TITLE_MIN_PERIMETER);
}
#include "ShapeController.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>

int main() {
    std::vector<std::shared_ptr<Shape>> shapes;
    std::string line;

    std::cout << PROMPT_ENTER_SHAPES;

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        auto shape = parseShape(line);
        if (shape) {
            shapes.push_back(shape);
            std::cout << MSG_ADDED_PREFIX << shape->ToString() << NEWLINE;
        }
    }

    if (shapes.empty()) {
        std::cout << MSG_NO_SHAPES;
        return 0;
    }

    std::cout << MSG_TOTAL_SHAPES << shapes.size() << NEWLINE;

    auto maxAreaShape = findMaxArea(shapes);
    auto minPerimeterShape = findMinPerimeter(shapes);

    printShapeInfo(maxAreaShape, TITLE_MAX_AREA);
    printShapeInfo(minPerimeterShape, TITLE_MIN_PERIMETER);

    return 0;
}
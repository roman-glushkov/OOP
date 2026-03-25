#pragma once
#include "../shapes/CPoint.h"
#include <cmath>

namespace GeometryUtils
{
    inline double Distance(CPoint p1, CPoint p2)
    {
        double dx = p1.x - p2.x;
        double dy = p1.y - p2.y;
        return std::sqrt(dx * dx + dy * dy);
    }
}
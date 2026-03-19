#include "shapes/CLineSegment.h"
#include "utils/GeometryUtils.h"
#include "utils/Config.h"
#include <sstream>
#include <iomanip>

CLineSegment::CLineSegment(CPoint start, CPoint end, uint32_t outlineColor): m_start(start), m_end(end), m_outlineColor(outlineColor) {}

double CLineSegment::GetArea() const
{
    return Config::DEFAULT;
}

double CLineSegment::GetPerimeter() const
{
    return GeometryUtils::Distance(m_start, m_end);
}

std::string CLineSegment::ToString() const
{
    std::ostringstream oss;
    oss << Config::LINE_FORMAT
        << m_start.x << Config::COMMA_SPACE << m_start.y << Config::ARROW
        << m_end.x << Config::COMMA_SPACE << m_end.y << Config::CLOSE_BRACKET;
    return oss.str();
}

uint32_t CLineSegment::GetOutlineColor() const
{
    return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
    return m_start;
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_end;
}
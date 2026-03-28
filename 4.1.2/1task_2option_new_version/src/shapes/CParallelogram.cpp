#include "shapes/CParallelogram.h"
#include "utils/GeometryUtils.h"
#include "utils/Config.h"
#include <sstream>
#include <iomanip>
#include <cmath>

CParallelogram::CParallelogram(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t outlineColor, uint32_t fillColor)
    : m_vertex1(vertex1), m_vertex2(vertex2), m_vertex3(vertex3), m_outlineColor(outlineColor), m_fillColor(fillColor)
{
    m_vertex4.x = vertex1.x + (vertex3.x - vertex2.x);
    m_vertex4.y = vertex1.y + (vertex3.y - vertex2.y);
}

double CParallelogram::GetArea() const
{
    double dx1 = m_vertex2.x - m_vertex1.x;
    double dy1 = m_vertex2.y - m_vertex1.y;
    double dx2 = m_vertex4.x - m_vertex1.x;
    double dy2 = m_vertex4.y - m_vertex1.y;
    return std::abs(dx1 * dy2 - dx2 * dy1);
}

double CParallelogram::GetPerimeter() const
{
    return GeometryUtils::Distance(m_vertex1, m_vertex2) + GeometryUtils::Distance(m_vertex2, m_vertex3) +
           GeometryUtils::Distance(m_vertex3, m_vertex4) + GeometryUtils::Distance(m_vertex4, m_vertex1);
}

std::string CParallelogram::ToString() const
{
    std::ostringstream oss;
    oss << Config::PARALLELOGRAM_FORMAT
        << m_vertex1.x << Config::COMMA_SPACE << m_vertex1.y << Config::COMMA_CLOSE
        << m_vertex2.x << Config::COMMA_SPACE << m_vertex2.y << Config::COMMA_CLOSE
        << m_vertex3.x << Config::COMMA_SPACE << m_vertex3.y << Config::COMMA_CLOSE
        << m_vertex4.x << Config::COMMA_SPACE << m_vertex4.y << Config::CLOSE_BRACKET;
    return oss.str();
}

uint32_t CParallelogram::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CParallelogram::GetFillColor() const
{
    return m_fillColor;
}

CPoint CParallelogram::GetVertex1() const
{
    return m_vertex1;
}

CPoint CParallelogram::GetVertex2() const
{
    return m_vertex2;
}

CPoint CParallelogram::GetVertex3() const
{
    return m_vertex3;
}

CPoint CParallelogram::GetVertex4() const
{
    return m_vertex4;
}
#include "shapes/CTriangle.h"
#include "utils/GeometryUtils.h"
#include "utils/Config.h"
#include <sstream>
#include <iomanip>
#include <cmath>

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t outlineColor, uint32_t fillColor)
    : m_vertex1(vertex1), m_vertex2(vertex2), m_vertex3(vertex3), m_outlineColor(outlineColor), m_fillColor(fillColor) {}

double CTriangle::GetArea() const
{
    double area = m_vertex1.x * (m_vertex2.y - m_vertex3.y) + m_vertex2.x * (m_vertex3.y - m_vertex1.y) + m_vertex3.x * (m_vertex1.y - m_vertex2.y);
    return std::abs(area) / Config::DEFAULT_2;
}

double CTriangle::GetPerimeter() const
{
    return GeometryUtils::Distance(m_vertex1, m_vertex2) + GeometryUtils::Distance(m_vertex2, m_vertex3) + GeometryUtils::Distance(m_vertex3, m_vertex1);
}

std::string CTriangle::ToString() const
{
    std::ostringstream oss;
    oss << Config::TRIANGLE_FORMAT
        << m_vertex1.x << Config::COMMA_SPACE << m_vertex1.y << Config::COMMA_CLOSE
        << m_vertex2.x << Config::COMMA_SPACE << m_vertex2.y << Config::COMMA_CLOSE
        << m_vertex3.x << Config::COMMA_SPACE << m_vertex3.y << Config::CLOSE_BRACKET;
    return oss.str();
}

uint32_t CTriangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
    return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
    return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
    return m_vertex3;
}
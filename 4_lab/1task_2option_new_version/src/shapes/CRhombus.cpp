#include "shapes/CRhombus.h"
#include "utils/GeometryUtils.h"
#include "utils/Config.h"
#include <sstream>
#include <iomanip>
#include <cmath>

CRhombus::CRhombus(CPoint center, double diagonal1, double diagonal2, uint32_t outlineColor, uint32_t fillColor)
    : m_center(center), m_diagonal1(diagonal1), m_diagonal2(diagonal2), m_outlineColor(outlineColor), m_fillColor(fillColor) {}

double CRhombus::GetArea() const
{
    return (m_diagonal1 * m_diagonal2) / Config::DEFAULT_2;
}

double CRhombus::GetPerimeter() const
{
    double halfD1 = m_diagonal1 / Config::DEFAULT_2;
    double halfD2 = m_diagonal2 / Config::DEFAULT_2;
    double side = std::sqrt(halfD1 * halfD1 + halfD2 * halfD2);
    return Config::DEFAULT_4 * side;
}

std::string CRhombus::ToString() const
{
    std::ostringstream oss;
    oss << Config::RHOMBUS_FORMAT
        << GetVertex1().x << Config::COMMA_SPACE << GetVertex1().y << Config::COMMA_CLOSE
        << GetVertex2().x << Config::COMMA_SPACE << GetVertex2().y << Config::COMMA_CLOSE
        << GetVertex3().x << Config::COMMA_SPACE << GetVertex3().y << Config::COMMA_CLOSE
        << GetVertex4().x << Config::COMMA_SPACE << GetVertex4().y << Config::CLOSE_BRACKET;
    return oss.str();
}

uint32_t CRhombus::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CRhombus::GetFillColor() const
{
    return m_fillColor;
}

CPoint CRhombus::GetVertex1() const
{
    return CPoint(m_center.x, m_center.y - m_diagonal1 / Config::DEFAULT_2);
}

CPoint CRhombus::GetVertex2() const
{
    return CPoint(m_center.x + m_diagonal2 / Config::DEFAULT_2, m_center.y);
}

CPoint CRhombus::GetVertex3() const
{
    return CPoint(m_center.x, m_center.y + m_diagonal1 / Config::DEFAULT_2);
}

CPoint CRhombus::GetVertex4() const
{
    return CPoint(m_center.x - m_diagonal2 / Config::DEFAULT_2, m_center.y);
}

CPoint CRhombus::GetCenter() const
{
    return m_center;
}

double CRhombus::GetDiagonal1() const
{
    return m_diagonal1;
}

double CRhombus::GetDiagonal2() const
{
    return m_diagonal2;
}
#include "shapes/CSquare.h"
#include "utils/GeometryUtils.h"
#include "utils/Config.h"
#include <sstream>
#include <iomanip>
#include <cmath>

CSquare::CSquare(CPoint leftTop, double side, uint32_t outlineColor, uint32_t fillColor)
    : m_leftTop(leftTop), m_side(side), m_outlineColor(outlineColor), m_fillColor(fillColor) {}

double CSquare::GetArea() const
{
    return m_side * m_side;
}

double CSquare::GetPerimeter() const
{
    return 4 * m_side;
}

std::string CSquare::ToString() const
{
    CPoint lt = m_leftTop;
    CPoint rt(m_leftTop.x + m_side, m_leftTop.y);
    CPoint rb(m_leftTop.x + m_side, m_leftTop.y + m_side);
    CPoint lb(m_leftTop.x, m_leftTop.y + m_side);

    std::ostringstream oss;
    oss << "Square [("
        << lt.x << ", " << lt.y << "), ("
        << rt.x << ", " << rt.y << "), ("
        << rb.x << ", " << rb.y << "), ("
        << lb.x << ", " << lb.y << ")]";

    return oss.str();
}
uint32_t CSquare::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CSquare::GetFillColor() const
{
    return m_fillColor;
}

CPoint CSquare::GetLeftTop() const
{
    return m_leftTop;
}

CPoint CSquare::GetRightBottom() const
{
    return CPoint(m_leftTop.x + m_side, m_leftTop.y + m_side);
}

double CSquare::GetSide() const
{
    return m_side;
}
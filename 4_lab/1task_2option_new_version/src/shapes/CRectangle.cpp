#include "shapes/CRectangle.h"
#include "utils/GeometryUtils.h"
#include "utils/Config.h"
#include <sstream>
#include <iomanip>
#include <cmath>

CRectangle::CRectangle(CPoint leftTop, double width, double height, uint32_t outlineColor, uint32_t fillColor)
    : m_leftTop(leftTop), m_width(width), m_height(height), m_outlineColor(outlineColor), m_fillColor(fillColor) {}

double CRectangle::GetArea() const
{
    return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
    return 2 * (m_width + m_height);
}

std::string CRectangle::ToString() const
{
    double x = m_leftTop.x;
    double y = m_leftTop.y;
    double w = m_width;
    double h = m_height;

    std::ostringstream oss;
    oss << "Rectangle [("
        << x << ", " << y << "), ("
        << x + w << ", " << y << "), ("
        << x + w << ", " << y + h << "), ("
        << x << ", " << y + h << ")]";

    return oss.str();
}

uint32_t CRectangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
    return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
    return CPoint(m_leftTop.x + m_width, m_leftTop.y + m_height);
}

double CRectangle::GetWidth() const
{
    return m_width;
}

double CRectangle::GetHeight() const
{
    return m_height;
}
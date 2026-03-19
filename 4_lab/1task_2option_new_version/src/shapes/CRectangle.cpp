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
    CPoint rightBottom(m_leftTop.x + m_width, m_leftTop.y + m_height);
    
    std::ostringstream oss;
    oss << Config::RECTANGLE_FORMAT
        << m_leftTop.x << Config::COMMA_SPACE << m_leftTop.y << Config::COMMA_CLOSE
        << rightBottom.x << Config::COMMA_SPACE << rightBottom.y << Config::CLOSE_BRACKET;
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
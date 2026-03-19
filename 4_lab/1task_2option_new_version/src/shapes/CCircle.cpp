#include "shapes/CCircle.h"
#include "utils/GeometryUtils.h"
#include "utils/Config.h"
#include <sstream>
#include <iomanip>
#include <cmath>

CCircle::CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor) 
    : m_center(center), m_radius(radius), m_outlineColor(outlineColor), m_fillColor(fillColor) {}

double CCircle::GetArea() const
{
    return Config::PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
    return 2 * Config::PI * m_radius;
}

std::string CCircle::ToString() const
{
    std::ostringstream oss;
    oss << "Circle [center: ("
        << m_center.x << ", " << m_center.y
        << "), radius: " << m_radius << "]";
    return oss.str();
}

uint32_t CCircle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CCircle::GetCenter() const
{
    return m_center;
}

double CCircle::GetRadius() const
{
    return m_radius;
}
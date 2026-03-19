#pragma once

#include "../interfaces/ISolidShape.h"
#include "CPoint.h"
#include <cstdint>

class CSquare : public ISolidShape
{
public:
    CSquare(CPoint leftTop, double side, uint32_t outlineColor, uint32_t fillColor);
    
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    uint32_t GetOutlineColor() const override;
    uint32_t GetFillColor() const override;
    CPoint GetLeftTop() const;
    CPoint GetRightBottom() const;
    double GetSide() const;

private:
    CPoint m_leftTop;
    double m_side;
    uint32_t m_outlineColor;
    uint32_t m_fillColor;
};
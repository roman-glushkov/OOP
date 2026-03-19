#pragma once

#include "../interfaces/ISolidShape.h"
#include "CPoint.h"
#include <cstdint>

class CRhombus : public ISolidShape
{
public:
    CRhombus(CPoint center, double diagonal1, double diagonal2, uint32_t outlineColor, uint32_t fillColor);

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    uint32_t GetOutlineColor() const override;
    uint32_t GetFillColor() const override;
    CPoint GetVertex1() const;
    CPoint GetVertex2() const;
    CPoint GetVertex3() const;
    CPoint GetVertex4() const;
    CPoint GetCenter() const;
    double GetDiagonal1() const;
    double GetDiagonal2() const;

private:
    CPoint m_center;
    double m_diagonal1;
    double m_diagonal2;
    uint32_t m_outlineColor;
    uint32_t m_fillColor;
};
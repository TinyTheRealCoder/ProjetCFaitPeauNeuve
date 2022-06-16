#include "Triangle.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

WX_DECLARE_LIST(wxPoint, MyPoints);

#include <wx/listimpl.cpp>

WX_DEFINE_LIST(MyPoints);

using namespace std; // Jamais dans un point h(pp) !

// R�servation m�moire de l'attribut statique de la classe Triangle
// static
unsigned int Triangle::m_triangleCount = 0;


Triangle::Triangle()
{
    std::cout << "Triangle (defaut)" << std::endl;
    m_triangleCount++;
}

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3, int IndProfond, const std::string& label, int red_fill, int green_fill, int blue_fill, int opacity_fill, unsigned char red_stroke, unsigned char green_stroke, unsigned char blue_stroke, int opacity_stroke, int stroke_width) : Forme(label, IndProfond, red_fill, blue_fill, green_fill, opacity_fill, red_stroke, blue_stroke, green_stroke, opacity_stroke, stroke_width)
{
    std::cout << "Triangle (riche)" << std::endl;
    m_triangleCount++;
    m_p1 = p1;
    m_p2 = p2;
    m_p3 = p3;
}

Triangle::~Triangle()
{
    std::cout << "~Triangle" << std::endl;
    m_triangleCount--;
}

Triangle::Triangle(const Triangle &other) :
    // Appel du contructeur de Forme avec un label
    Forme(other.GetLabel(), other.GetIndProfond(), other.m_red_fill, other.m_blue_fill, other.m_green_fill, other.m_opacity_fill, other.m_red_stroke, other.m_blue_stroke, other.m_green_stroke, other.m_opacity_stroke, other.m_stroke_width),
    // Appel des 3 constructeurs par copies des Points
    m_p1(other.m_p1),
    m_p2(other.m_p2),
    m_p3(other.m_p3)
{
    std::cout << "Triangle (copie)" << std::endl;
    m_triangleCount++;
}

Triangle &Triangle::operator=(const Triangle &other)
{
    if (this == &other) return *this; // handle self assignment

    std::cout << "Triangle (affectation)" << std::endl;
    *m_label = *other.m_label;
    m_p1 = other.m_p1;
    m_p2 = other.m_p2;
    m_p3 = other.m_p3;
    return *this;
}

void Triangle::draw(wxClientDC& drawC) 
{	
    drawC.SetBrush(wxColour(m_red_fill, m_green_fill, m_blue_fill, m_opacity_fill));
    drawC.SetPen(wxColour(m_red_stroke, m_green_stroke, m_blue_stroke, m_opacity_stroke));
    wxPoint points[3];

    points[0] = wxPoint(m_p1.GetX(),m_p1.GetY());
    points[1] = wxPoint(m_p2.GetX(),m_p2.GetY());
    points[2] = wxPoint(m_p3.GetX(),m_p3.GetY());

    drawC.DrawPolygon(WXSIZEOF(points),points);
}

/*
void Triangle::Display() const
{
    std::cout << "Triangle " << GetLabel() << "="
              << "(" << m_p1.GetX() << "," << m_p1.GetY() << ")"
              << "(" << m_p2.GetX() << "," << m_p2.GetY() << ")"
              << "(" << m_p3.GetX() << "," << m_p3.GetY() << ")" << std::endl;
}
*/

//MODIFY
//-------------------------------------------
std::string Triangle::Display()
//-------------------------------------------
{
    return "<polygon points=\"" + std::to_string(m_p1.GetX()) + " " + std::to_string(m_p1.GetY()) + "," + std::to_string(m_p2.GetX()) + " " + std::to_string(m_p2.GetY()) + "," + std::to_string(m_p3.GetX()) + " " + std::to_string(m_p3.GetY()) + "\" stroke = \"\" stroke-line=\"\" fill=\"\" >";
}

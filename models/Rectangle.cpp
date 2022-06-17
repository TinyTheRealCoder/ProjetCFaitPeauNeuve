#include <iostream>
#include <cstdlib>
#include <cmath> // pour sqrt

// Inutile d'include Point.h car il est inclut dans Rectangle.h
#include "Rectangle.h"

using namespace std;

// Allocation de la m�moire pour l'attribut statique
// static
unsigned int Rectangle::m_rectCount = 0;

//-------------------------------------------
Rectangle::Rectangle(int x, int y, int w, int h, int IndProfond, const std::string& label, int red_fill, int green_fill, int blue_fill, int opacity_fill, unsigned char red_stroke, unsigned char green_stroke, unsigned char blue_stroke, int opacity_stroke, int stroke_width) :

    // Appel du constructeur de Forme avec un label

    Forme(label, IndProfond, red_fill, blue_fill, green_fill, opacity_fill, red_stroke, blue_stroke, green_stroke, opacity_stroke, stroke_width)
    
//-------------------------------------------
// attention, cette version appelle le constructeur par d�faut de Point
// comme le compilateur ne l?a pas cr��, il faut le rajouter dans Point
{
    cout << __func__ << " @=" << this << "\n";
    m_corner.SetX(x);
    m_corner.SetY(y);
    m_w = w;
    m_h = h;
    m_rectCount++;
}

//-------------------------------------------
Rectangle::Rectangle(const Point& p, int w, int h, int IndProfond, const std::string& label, int red_fill, int green_fill, int blue_fill, int opacity_fill, unsigned char red_stroke, unsigned char green_stroke, unsigned char blue_stroke, int opacity_stroke, int stroke_width) :
    Forme(label, IndProfond, red_fill, blue_fill, green_fill, opacity_fill, red_stroke, blue_stroke, green_stroke, opacity_stroke, stroke_width),
    m_corner(p.GetX(),p.GetY()),
    m_w(w),
    m_h(h)
//-------------------------------------------
// cette version n'appelle pas le constructeur par d�faut de Point
// car on utilise la liste d'initialisation
// On aurait pu simplifier en cr�ant un constructeur par copie pour la classe Point
{
    cout << __func__ << " @=" << this << "\n";
    m_rectCount++;
}


//-------------------------------------------
Rectangle::~Rectangle()
//-------------------------------------------
{
    cout << __func__ << " @=" << this << "\n";
    m_rectCount--;
}

//-------------------------------------------
void Rectangle::SetCorner(const Point& p)
//-------------------------------------------
{
    // On utilise operator= d�finit automatiquement par le compilateur
    m_corner = p;
}

//-------------------------------------------
void Rectangle::SetWidth(int w)
//-------------------------------------------
{
    m_w = w;
}

//-------------------------------------------
void Rectangle::SetHeight(int h)
//-------------------------------------------
{
    m_h = h;
}

//-------------------------------------------
const Point& Rectangle::GetCorner() const
//-------------------------------------------
{
    // Retourne une r�f�rence const sur m_corner
    // pour �viter une copie d'objet
    return m_corner;
}

//-------------------------------------------
int Rectangle::GetWidth() const
//-------------------------------------------
{
    return m_w;
}

//-------------------------------------------
int Rectangle::GetHeight() const
//-------------------------------------------
{
    return m_h;
}

//-------------------------------------------
std::string Rectangle::Display()
//-------------------------------------------
{
    if(m_w < 0){
        m_corner.SetX(m_corner.GetX()+m_w);
        m_w = -m_w;
    }
    
    if(m_h < 0){
        m_corner.SetY(m_corner.GetY()+m_h);
        m_h = -m_h;
    }

    return "<rect x=\"" + std::to_string(m_corner.GetX()) + "\" y=\"" + std::to_string(m_corner.GetY()) + "\" width=\"" + std::to_string(m_w) + "\" height=\"" + std::to_string(m_h) + + "\" stroke=\"rgb(" +std::to_string(m_red_stroke)+ "," +std::to_string(m_green_stroke)+ "," +std::to_string(m_blue_stroke)+ ")\" stroke-opacity=\"" +std::to_string(m_opacity_stroke) + "\" stroke-width=\"" + std::to_string(m_stroke_width)  +"\" fill=\"rgb(" +std::to_string(m_red_fill)+ "," +std::to_string(m_green_fill)+ "," +std::to_string(m_blue_fill)+ ")\" fill-opacity=\"" +std::to_string(m_opacity_fill/255) + "\" />";
}

//-------------------------------------------
void Rectangle::Move(int dX, int dY)
//-------------------------------------------
{
    cout << __func__ << " @=" << this << endl;
    m_corner.Move(dX, dY);
}

//-------------------------------------------
int Rectangle::GetRectCount()
//-------------------------------------------
{
    return Rectangle::m_rectCount;
}

//-------------------------------------------
bool Rectangle::IsInside(int mouse_x, int mouse_y)
//-------------------------------------------
{
    int x_start = GetCorner().GetX();
    int y_start = GetCorner().GetY();
    int x_end = GetCorner().GetX() + m_w;
    int y_end = GetCorner().GetY() + m_h;

    if(x_start > x_end){
        int tmp = x_start;
        x_start = x_end;
        x_end = tmp;
    }

    if(y_start > y_end){
        int tmp = y_start;
        y_start = y_end;
        y_end = tmp;
    }

    return (mouse_x >= x_start && mouse_x <= x_end && mouse_y >= y_start && mouse_y <= y_end);
}

//-------------------------------------------
void Rectangle::draw(wxClientDC& drawC) 
//-------------------------------------------
{	
    drawC.SetBrush(wxColour(m_red_fill, m_green_fill, m_blue_fill, m_opacity_fill));
    wxPen* xPen = new wxPen(wxColour(m_red_stroke,m_green_stroke,m_blue_stroke,m_opacity_stroke));
	xPen->SetWidth(m_stroke_width);
	drawC.SetPen(*xPen);
    drawC.DrawRectangle(wxPoint(m_corner.GetX(),m_corner.GetY()),wxSize(m_w,m_h));
}
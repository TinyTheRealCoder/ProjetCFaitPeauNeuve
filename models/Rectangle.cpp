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
Rectangle::Rectangle(int x, int y, int w, int h, int IndProfond, const std::string& label, int red_fill, int green_fill, int blue_fill, int opacity_fill, int red_stroke, int green_stroke, int blue_stroke, int opacity_stroke, int stroke_width) :

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
Rectangle::Rectangle(const Point& p, int w, int h, int IndProfond, const std::string& label, int red_fill, int green_fill, int blue_fill, int opacity_fill, int red_stroke, int green_stroke, int blue_stroke, int opacity_stroke, int stroke_width) :
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

void Rectangle::draw(wxClientDC& drawC) 
{	
    drawC.DrawRectangle(wxPoint(m_corner.GetX(),m_corner.GetY()),wxSize(m_w,m_h));
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

//MODIFY
//-------------------------------------------
std::string Rectangle::Display()
//-------------------------------------------
{
    return "<rect x=\"" + std::to_string(m_corner.GetX()) + "\" y=\"" + std::to_string(m_corner.GetY()) + "\" width=\"" + std::to_string(m_w) + "\" height=\"" + std::to_string(m_h) + "\" stroke=\"\" stroke-line=\"\" fill=\"\" >";
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
bool Rectangle::IsInside(const Rectangle &r) const
//-------------------------------------------
// retourne true si le rectangle est enti�rement � l'int�rieur (inclus) dans le Rectangle r
// si r1 est inclus dans r2
{
    // On r�cup�re les valeurs des points du rectangle
    int x1r1 = GetCorner().GetX();
    int y1r1 = GetCorner().GetY();
    int x2r1 = x1r1 + m_w;
    int y2r1 = y1r1 + m_h;
    int x1r2 = r.GetCorner().GetX();
    int y1r2 = r.GetCorner().GetY();
    int x2r2 = x1r2 + r.GetWidth();
    int y2r2 = y1r2 + r.GetHeight();

    // On v�rifier que r est inclus dans ce Rectangle (this)
    return ((x1r1 > x1r2 && x1r1 < x2r2) || (x1r1 < x1r2 && x1r1 > x2r2)) &&
           ((x1r1 > x1r2 && x1r1 < x2r2) || (x1r1 < x1r2 && x1r1 > x2r2));
}

// On red�finit les m�thodes virtuelles pour les affiner
/*float Rectangle::Surface() const
{
    return (float)(m_w * m_h);
}

float Rectangle::Perimeter() const
{
    return (float)(2*m_w + 2*m_h);;
}*/

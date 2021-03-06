#include "Cercle.h"
#include <iostream>
#include <cstdlib>

#define _USE_MATH_DEFINES   // To include PI value
#include <math.h>

using namespace std;    // jamais dans un .h(pp) !

// D�claration de l'attribut statique pour r�servation m�moire
// static
unsigned int Cercle::m_circleCount = 0;

// Constructeur riche. On appelle une version sp�cifique du construceur
// de Forme et on initilise le centre et le radius de m�me
Cercle::Cercle(Point centre, int radius, int IndProfond, string label, int red_fill, int green_fill, int blue_fill, int opacity_fill, unsigned char red_stroke, unsigned char green_stroke, unsigned char blue_stroke, int opacity_stroke, int stroke_width) :
    Forme(label, IndProfond, red_fill, blue_fill, green_fill, opacity_fill, red_stroke, blue_stroke, green_stroke, opacity_stroke, stroke_width),
    m_center(centre),
    m_radius(radius)
{
    cout << "Cercle (riche)" << endl;
    m_circleCount++;
}

// constructeur par d�faut, le constructeur par d�faut de
// Forme est automatiquement appel�
Cercle::Cercle()
{
    cout << "Cercle (defaut)" << endl;
    m_circleCount++;
}

// constructeur de copie
Cercle::Cercle(const Cercle &other) : Forme(other.GetLabel(), other.GetIndProfond(), other.m_red_fill, other.m_blue_fill, other.m_green_fill, other.m_opacity_fill, other.m_red_stroke, other.m_blue_stroke, other.m_green_stroke, other.m_opacity_stroke, other.m_stroke_width), m_center(other.m_center), m_radius(other.m_radius)
{
    cout << "Cercle (copie)" << endl;
    m_circleCount++;
}

Cercle::~Cercle()
{
    cout << "~Cercle" << endl;
    m_circleCount--;
}

Cercle &Cercle::operator=(const Cercle &other)
{
    if (this == &other) return *this; // handle self assignment

    cout << "Cercle (affectation)" << endl;
    *m_label = *other.m_label;
    m_center = other.m_center;
    m_radius = other.m_radius;
    m_IndProfond = other.m_IndProfond;
    return *this;
}

//-------------------------------------------
std::string Cercle::Display()
//-------------------------------------------
{
    return "<circle cx=\"" + std::to_string(m_center.GetX()) + "\" cy=\"" + std::to_string(m_center.GetY()) + "\" r=\"" + std::to_string(m_radius) + "\" stroke=\"rgb(" +std::to_string(m_red_stroke)+ "," +std::to_string(m_green_stroke)+ "," +std::to_string(m_blue_stroke)+ ")\" stroke-opacity=\"" +std::to_string(m_opacity_stroke/255) + "\" stroke-width=\"" + std::to_string(m_stroke_width)  +"\" fill=\"rgb(" +std::to_string(m_red_fill)+ "," +std::to_string(m_green_fill)+ "," +std::to_string(m_blue_fill)+ ")\" fill-opacity=\"" +std::to_string(m_opacity_fill/255) + "\" />";
}

//-------------------------------------------
bool Cercle::IsInside(int mouse_x, int mouse_y)
//------------------------------------------- 
{
    int r1 = sqrt(pow(m_center.GetX()-mouse_x, 2) + pow(m_center.GetY()-mouse_y, 2));
    return (r1 <= m_radius);
}

//-------------------------------------------
void Cercle::draw(wxClientDC& drawC) 
//-------------------------------------------
{	
    drawC.SetBrush(wxColour(m_red_fill, m_green_fill, m_blue_fill, m_opacity_fill));
    wxPen* xPen = new wxPen(wxColour(m_red_stroke,m_green_stroke,m_blue_stroke,m_opacity_stroke));
	xPen->SetWidth(m_stroke_width);
	drawC.SetPen(*xPen);
    drawC.DrawCircle(wxPoint(m_center.GetX(),m_center.GetY()),(m_radius));
}

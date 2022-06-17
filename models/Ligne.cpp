#include <iostream>
#include <cstdlib>
#include <string>

#include "Ligne.h"

using namespace std;

//static
int Ligne::nbLigne = 0;

//Default constructor
Ligne::Ligne() : Forme()
{
    //p1 = new Point();
    //p2 = new Point();
}

//Constructor

Ligne::Ligne(const Point& p1Tmp, const Point& p2Tmp, int IndProfond, const std::string& label, int red_fill, int green_fill, int blue_fill, int opacity_fill, unsigned char red_stroke, unsigned char green_stroke, unsigned char blue_stroke, int opacity_stroke, int stroke_width) : Forme(label, IndProfond, red_fill, blue_fill, green_fill, opacity_fill, red_stroke, blue_stroke, green_stroke, opacity_stroke, stroke_width)
{
    p1 = p1Tmp;
    p2 = p2Tmp;

    //Point center((x1 + x2)/2, (y1 + y2)/2);
    //Forme(string("Ligne"), center);

}

//Copy constructor

Ligne::Ligne(const Ligne& copy): Forme(copy.GetLabel(), copy.GetIndProfond(), copy.m_red_fill, copy.m_blue_fill, copy.m_green_fill, copy.m_opacity_fill, copy.m_red_stroke, copy.m_blue_stroke, copy.m_green_stroke, copy.m_opacity_stroke, copy.m_stroke_width)
{
    p1.SetX(copy.p1.GetX());
    p2.SetX(copy.p2.GetX());
    p1.SetY(copy.p1.GetY());
    p2.SetY(copy.p2.GetY());
}

//Destructeur
Ligne::~Ligne()
{
    cout << "~Ligne" << endl;
    nbLigne--;
}

// Accesseur 

//Setter

void Ligne::SetX1(int x)
{
    p1.SetX(x);
}

void Ligne::SetX2(int x)
{
    p2.SetX(x);
}

void Ligne::SetY1(int y)
{
    p1.SetY(y);
}

void Ligne::SetY2(int y)
{
    p2.SetY(y);
}

//GETTERS

int Ligne::GetX1()
{
    return p1.GetX();
}

int Ligne::GetX2()
{
    return p2.GetX();
}

int Ligne::GetY1()
{
    return p1.GetY();
}

int Ligne::GetY2()
{
    return p2.GetY();
}

void Ligne::draw(wxClientDC& drawC) 
{	
    drawC.SetBrush(wxColour(m_red_fill, m_green_fill, m_blue_fill, m_opacity_fill));
    wxPen* xPen = new wxPen(wxColour(m_red_stroke,m_green_stroke,m_blue_stroke,m_opacity_stroke));
	xPen->SetWidth(m_stroke_width);
	drawC.SetPen(*xPen);
    drawC.DrawLine(wxPoint(p1.GetX(),p1.GetY()),wxPoint(p2.GetX(),p2.GetY()));
}

//MODIFY
//-------------------------------------------
std::string Ligne::Display()
//-------------------------------------------
{
    // On affiche le nom
    
    return "<line x1=\"" + std::to_string(p1.GetX()) + "\" y1=\"" + std::to_string(p1.GetY()) + "\" x2=\"" + std::to_string(p2.GetX()) + "\" x2=\"" + std::to_string(p2.GetY()) + "\" stroke=\"rgba(" +std::to_string(m_red_stroke)+ "," +std::to_string(m_green_stroke)+ "," +std::to_string(m_blue_stroke)+ "," +std::to_string(m_opacity_stroke) + ")\" stroke-line=\"" + std::to_string(m_stroke_width)  +"\" fill=\"rgba(" +std::to_string(m_red_fill)+ "," +std::to_string(m_green_fill)+ "," +std::to_string(m_blue_fill)+ "," +std::to_string(m_opacity_fill) + ")\" >";
    
}

bool Ligne::IsInside(int mouse_x, int mouse_y) {

    float r1 = sqrt(pow(p1.GetX()-mouse_x, 2) + pow(p1.GetY()-mouse_y, 2));
    float r2 = sqrt(pow(p2.GetX()-mouse_x, 2) + pow(p2.GetY()-mouse_y, 2));
    float r3 = sqrt(pow(p2.GetX()-p1.GetX(), 2) + pow(p2.GetY()-p1.GetY(), 2));
    return ((r1+r2) <= (r3 + 0.3f + (m_stroke_width/4.0f)) );

}


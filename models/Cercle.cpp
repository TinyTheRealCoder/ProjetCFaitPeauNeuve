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
Cercle::Cercle(Point centre, int radius, int IndProfond, string label) :
    Forme(label, IndProfond),
    m_center(centre),
    m_radius(radius)
{
    cout << "Cercle (riche)" << endl;
    m_circleCount++;
}

void Cercle::draw(wxClientDC& drawC) 
{	
    drawC.DrawCircle(wxPoint(m_center.GetX(),m_center.GetY()),(m_radius));
}
/* Alternative
Cercle::Cercle(Point centre, int radius, int IndProfond, string label)
{
    m_center = centre;
    m_radius = radius;
    m_label = label;
    cout << "Cercle (riche)" << endl;
    SetLabel(label);
    m_circleCount++;
}
*/

// constructeur par d�faut, le constructeur par d�faut de
// Forme est automatiquement appel�
Cercle::Cercle()
{
    cout << "Cercle (defaut)" << endl;
    m_circleCount++;
}

// constructeur de copie
Cercle::Cercle(const Cercle &other) : Forme(other.GetLabel(), other.GetIndProfond()), m_center(other.m_center), m_radius(other.m_radius)
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

//MODIFY
//-------------------------------------------
std::string Cercle::Display()
//-------------------------------------------
{
    return "<circle cx=\"" + std::to_string(m_center.GetX()) + "\" cy=\"" + std::to_string(m_center.GetY()) + "\" r=\"" + std::to_string(m_radius) + "\" stroke=\"\" stroke-line=\"\" fill=\"\" >";
}

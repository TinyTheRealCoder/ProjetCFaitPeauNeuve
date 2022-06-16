#include <iostream>
#include "Forme.h"

using namespace std;

Forme::Forme()
{
    cout << "Forme (defaut)" << endl;
    // On alloue dynamiquement un label avec une chaine vide et une profondeur avec une chaine vide
    m_label = new string;
    m_IndProfond = 0;
    m_red_fill = 0;
    m_blue_fill = 0;
    m_green_fill = 0;
    m_stroke_color = "black";
    m_stroke_width = 1;
}

Forme::Forme(const std::string& label, int IndProfondeur, int red_fill, int green_fill, int blue_fill, std::string stroke_color, int stroke_width)
{
    cout << "Forme (avec un label et une profondeur)" << endl;
    // On alloue dynamiquement un label et une profondeur avec une chaine vide
    m_label = new string(label);
    m_IndProfond = IndProfondeur;
    m_red_fill = red_fill;
    m_blue_fill = blue_fill;
    m_green_fill = green_fill;
    m_stroke_color = stroke_color;
    m_stroke_width = stroke_width;
}

Forme::Forme(const Forme& other)
{
    cout << "Forme (avec un label et une profondeur)" << endl;
    // On alloue dynamiquement une copie de la profondeur et du label de other
    m_label = new string(*(other.m_label));
    m_IndProfond = other.m_IndProfond;
    m_red_fill = other.m_red_fill;
    m_blue_fill = other.m_blue_fill;
    m_green_fill = other.m_green_fill;
    m_stroke_color = other.m_stroke_color;
    m_stroke_width = other.m_stroke_width;
}

// virtual
Forme::~Forme()
{
    cout << "~Forme" << endl;
    delete m_label; 
}

Forme& Forme::operator=(const Forme& other)
{
    // La Forme contient deux attribut, le label et IndProfond, on peut utiliser SetLabel
    SetLabel(*(other.m_label));
    SetIndProfond(other.m_IndProfond);

    // On renvoit une référence sur l'objet courant
    return *(this);
}

void Forme::SetLabel(const std::string& label)
{
    delete m_label;
    // On alloue une nouvelle copie de la chaine
    m_label = new string(label);
}

std::string Forme::GetLabel() const
{
    // On renvoie une copie de la chaine
    return *(m_label);
}

void Forme::SetIndProfond(int IndProfondeur)
{
    m_IndProfond = IndProfondeur;
}

int Forme::GetIndProfond() const
{
    // On renvoie une copie de la chaine
    return m_IndProfond;
}


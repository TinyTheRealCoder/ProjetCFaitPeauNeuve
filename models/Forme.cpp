#include <iostream>
#include "Forme.h"

using namespace std;

Forme::Forme()
{
    cout << "Forme (defaut)" << endl;
    // On alloue dynamiquement un label avec une chaine vide et une profondeur avec une chaine vide
    m_label = new string;
    m_IndProfond = 0;
}

Forme::Forme(const std::string& label, int IndProfondeur)
{
    cout << "Forme (avec un label et une profondeur)" << endl;
    // On alloue dynamiquement un label et une profondeur avec une chaine vide
    m_label = new string(label);
    m_IndProfond = IndProfondeur;
}

Forme::Forme(const Forme& other)
{
    cout << "Forme (avec un label et une profondeur)" << endl;
    // On alloue dynamiquement une copie de la profondeur et du label de other
    m_label = new string(*(other.m_label));
    m_IndProfond = other.m_IndProfond;
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


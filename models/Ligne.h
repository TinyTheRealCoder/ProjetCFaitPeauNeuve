#ifndef __LIGNE_H__
#define __LIGNE_H__

#include "Forme.h"
#include "Point.h"
#include <iostream>

class Ligne : public Forme
{
public:
    // Construction par défaut, par copie, avec paramètres
    Ligne();
    Ligne(const Point& p1, const Point& p2, int IndProfond, const std::string& label, int red_fill, int green_fill, int blue_fill, std::string stroke_color, int stroke_width);
    Ligne(const Ligne& copy);
    
    // Destructeur virtuel car on peut dériver cette classe
    ~Ligne();

    // Opérateur d'affectation
    Ligne &operator=(const Ligne& copy);

    // Méthodes virtuelles pour surcharger celles de la classe Mère
    //virtual void Display() const final;
	//virtual void Longueur() const override;

    void SetX1(int x);
    void SetX2(int x);
    void SetY1(int y);
    void SetY2(int y);

    int GetX1();
    int GetX2();
    int GetY1();
    int GetY2();
    
    void draw(wxClientDC& drawC) override;

    //MODIFY
    virtual std::string Display();

private:    // Could be protected
    Point p1;
    Point p2;
    static int nbLigne;

};
#endif // __LIGNE_H__

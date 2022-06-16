#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include <string>

#include "Forme.h"
#include "Point.h"

//-------------------------------------------
class Rectangle : public Forme
//-------------------------------------------
{
public:                                     // interface publique de la classe
    // Ici on rajoute une label
    Rectangle(int x, int y, int w, int h, int IndProfond, const std::string& label);  // constructeur
    Rectangle(const Point& p, int w, int h, int IndProfond, const std::string& label);// constructeur
    ~Rectangle();                           // destructeur

    // Setters
    void SetCorner(const Point& p);
    void SetWidth(int w);
    void SetHeight(int h);

    // Getters
    const Point& GetCorner() const;         // On retourne une r�f�rence const sur m_corner
    int GetWidth() const;
    int GetHeight() const;

    // Fonction utilitaires
    void Move(int dX, int dY);                  // d�place le rectangle
    bool IsInside(const Rectangle &r) const;    // v�rifie l'inclusion

    //MODIFY
    virtual std::string Display() override;

    void draw(wxClientDC& drawC) override;

    // On rajoute les autres m�thodes virtuelles
    //virtual float Surface() const override;
    //virtual float Perimeter() const override;

    // M�thode statique pour le comptage de points
    static int GetRectCount();              // retourne le nombre de rectangles

private: // invisible � l?utilisateur de la classe
    Point m_corner;         // Le point
    int m_w;                // les dimensions
    int m_h;                // du rectangle

    static unsigned int m_rectCount; // donnee commune � tous les rectangles
};



#endif // __RECTANGLE_H__

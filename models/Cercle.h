#ifndef __CERCLE_H__
#define __CERCLE_H__

#include "Forme.h"
#include "Point.h"
#include <iostream>

class Cercle : public Forme
{
public:
    // Construction par d�faut, par copie, avec param�tres
    Cercle();
    Cercle(const Cercle &other);
    Cercle(Point centre, int radius, int IndProfond, std::string label, int red_fill, int green_fill, int blue_fill, int opacity_fill, int red_stroke, int green_stroke, int blue_stroke, int opacity_stroke, int stroke_width);

    // Destructeur virtuel car on peut d�river cette classe
    ~Cercle();

    // Op�rateur d'affectation
    Cercle &operator=(const Cercle &other);
    
    void draw(wxClientDC& drawC) override;
    
    //Mise en balise SVG
    virtual std::string Display() override;
    

private:    
    Point m_center;
    int m_radius;

    static unsigned int m_circleCount;
};
#endif // __CERCLE_H__

#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <string>

#include "Forme.h"
#include "Point.h"

class Triangle : public Forme
{

    public:

        // Constructeurs
        // Pour aller au bout du raisonnement, le passage par r�f�rence const est plus
        // rapide et plus s�r (pas de modification possible des objets, pas de copies inutiles)
        Triangle();
        Triangle(const Point& p1, const Point& p2, const Point& p3, int IndProfond, const std::string& label, int red_fill, int green_fill, int blue_fill, int opacity_fill, unsigned char red_stroke, unsigned char green_stroke, unsigned char blue_stroke, int opacity_stroke, int stroke_width);
        Triangle(const Triangle &other);

        // Destructeur virtuel
        ~Triangle();

        // Affectation
        Triangle &operator=(const Triangle &other);

        //Mise en balise SVG
        virtual std::string Display() override;
        
        //Dessine la forme dans drawC
        void draw(wxClientDC& drawC) override;

        //Detecte si la souris est sur la forme
        virtual bool IsInside(int mouse_x, int mouse_y) override;    // v�rifie l'inclusion
        
    private:

        //Points de construction du triangle
        Point m_p1;
        Point m_p2;
        Point m_p3;

        // Pour compter les triangles
        static unsigned int m_triangleCount;
        
};

#endif // __TRIANGLE_H__

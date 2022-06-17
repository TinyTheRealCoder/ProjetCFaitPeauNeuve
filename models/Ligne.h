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
        Ligne(const Point& p1, const Point& p2, int IndProfond, const std::string& label, int red_fill, int green_fill, int blue_fill, int opacity_fill, unsigned char red_stroke, unsigned char green_stroke, unsigned char blue_stroke, int opacity_stroke, int stroke_width);
        Ligne(const Ligne& copy);
        
        // Destructeur virtuel car on peut dériver cette classe
        ~Ligne();

        // Opérateur d'affectation
        Ligne &operator=(const Ligne& copy);

        // Accesseurs
        void SetX1(int x);
        void SetX2(int x);
        void SetY1(int y);
        void SetY2(int y);

        int GetX1();
        int GetX2();
        int GetY1();
        int GetY2();
        
        //Dessine la forme dans drawC
        void draw(wxClientDC& drawC) override;

        //Detecte si la souris est sur la forme (Ou juste a coté petite marge autorisé car sinon demande trop de précision)
        virtual bool IsInside(int mouse_x, int mouse_y) override;    // v�rifie l'inclusion

        //Mise en balise SVG
        virtual std::string Display();

    private:    // Could be protected
        
        //Points de construction de la ligne
        Point p1;
        Point p2;

        //Nombre de lignes
        static int nbLigne;

};
#endif // __LIGNE_H__

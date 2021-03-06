#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include <string>

#include "Forme.h"
#include "Point.h"

//-------------------------------------------
class Rectangle : public Forme
//-------------------------------------------
{

    public:                           // interface publique de la classe  
            
        // Ici on rajoute une label
        Rectangle(int x, int y, int w, int h, int IndProfond, const std::string& label, int red_fill, int green_fill, int blue_fill, int opacity_fill, unsigned char red_stroke, unsigned char green_stroke, unsigned char blue_stroke, int opacity_stroke, int stroke_width);  // constructeur
        Rectangle(const Point& p, int w, int h, int IndProfond, const std::string& label, int red_fill, int green_fill, int blue_fill, int opacity_fill, unsigned char red_stroke, unsigned char green_stroke, unsigned char blue_stroke, int opacity_stroke, int stroke_width);// constructeur
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

        //Detecte si la souris est sur la forme
        virtual bool IsInside(int mouse_x, int mouse_y) override;    // v�rifie l'inclusion

        //Mise en balise SVG
        virtual std::string Display() override;

        //Dessine la forme dans drawC
        void draw(wxClientDC& drawC) override;

        // M�thode statique pour le comptage de points
        static int GetRectCount();              // retourne le nombre de rectangles

    private:

        Point m_corner;         // Le point
        int m_w;                // les dimensions
        int m_h;                // du rectangle

        static unsigned int m_rectCount; // donnee commune � tous les rectangles
};



#endif // __RECTANGLE_H__

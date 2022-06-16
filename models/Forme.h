
#ifndef __FORME_H__
#define __FORME_H__

//LIBRAIRIE
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include<wx/filedlg.h>
#include <wx/image.h>
#include <wx/file.h>
#include <wx/bitmap.h>
#include <bits/stdc++.h>

//STANDAR
#include <string>
#include <iostream>

class Forme
{
public:
    // Construction/Destruction
    Forme();
    Forme(const std::string& label, int IndProfondeur, int red_fill, int green_fill, int blue_fill, std::string stroke_color, int stroke_width);    // Avec une string
    Forme(const Forme& other);          // Construction par recopie
    virtual ~Forme();

    // Operator d'affectation
    Forme& operator=(const Forme& other);

    // Accesseur
    void SetLabel(const std::string& s);
    std::string GetLabel() const;
    
    void SetIndProfond(int IndProfondeur);
    int GetIndProfond() const; 
    virtual void draw(wxClientDC& drawC){};

    //Affiche de la forme
    virtual std::string Display() {
        return "";
    }

protected:  // ou private
    std::string * m_label;
    int m_IndProfond; 

    //Gestion de la couleur de fond
    int m_red_fill;
    int m_green_fill;
    int m_blue_fill;

    //Gestion de la bordure de la forme
    std::string m_stroke_color;
    int m_stroke_width;
};

#endif // __FORME_H__

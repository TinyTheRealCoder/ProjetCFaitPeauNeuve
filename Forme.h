
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
    Forme(const std::string& label, int IndProfondeur);    // Avec une string
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

    //MODIFY
    //---
    virtual std::string Display() {
        return "";
    }
    //---

    //virtual float Surface() const { return 0.0f; }
    //virtual float Perimeter() const { return 0.0f; }
    //virtual float Longueur() const { return 0.0f; }

protected:  // ou private
    std::string * m_label;
    int m_IndProfond; 
};

#endif // __FORME_H__

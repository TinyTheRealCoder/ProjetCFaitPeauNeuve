#ifndef __DESSIN_H__
#define __DESSIN_H__

#include "Forme.h"
#include <vector>

class Dessin
{

    public:

        //Contructeur, Destructeur, Opérateurs
        Dessin();
        Dessin(const Dessin& dessin);
        Dessin& operator=(const Dessin& dessin);
        ~Dessin();

        //Getteur
        std::vector<Forme*> getVector();

        //Modification sur le vecteur de formes
        void addVector(Forme* forme);
        void removeVector(int i);
        void SendBackVector(int i);
        void SendFrontVector(int i);

    private:

        std::vector<Forme*> dessins;
        

};

#endif //__DESSIN_H__

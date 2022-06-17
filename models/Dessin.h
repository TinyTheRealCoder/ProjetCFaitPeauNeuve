#ifndef __DESSIN_H__
#define __DESSIN_H__

#include "Forme.h"
#include <vector>

class Dessin
{

public:

    Dessin();
    Dessin(const Dessin& dessin);
    Dessin& operator=(const Dessin& dessin);
    ~Dessin();

    std::vector<Forme*> getVector();
    void addVector(Forme* forme);
    void removeVector(int i);
    void SendBackVector(int i);
    void SendFrontVector(int i);

private:

    std::vector<Forme*> dessins;

};

#endif //__DESSIN_H__

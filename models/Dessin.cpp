#include "Dessin.h"
#include "Forme.h"
#include <vector>

using namespace std;

Dessin:: Dessin()
{
	
}

Dessin::Dessin(const Dessin& dessin)
{
	this->dessins = dessin.dessins;
}

Dessin::~Dessin()
{
	
}

std::vector<Forme*> Dessin::getVector()
{
return dessins;
}

void Dessin::addVector(Forme* forme)
{
 this->dessins.push_back(forme);
}

void Dessin::removeVector(int i)
{
 this->dessins.erase(dessins.begin()+i);
}

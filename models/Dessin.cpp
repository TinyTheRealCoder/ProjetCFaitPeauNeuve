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

//-------------------------------------------
std::vector<Forme*> Dessin::getVector()
//-------------------------------------------
{

	return dessins;

}

//-------------------------------------------
void Dessin::addVector(Forme* forme)
//-------------------------------------------
{

	dessins.push_back(forme);

}

//-------------------------------------------
void Dessin::removeVector(int i)
//-------------------------------------------
{

	dessins.erase(dessins.begin()+i);

}

//-------------------------------------------
void Dessin::SendBackVector(int i)
//-------------------------------------------
{

	if((i-1) >= 0){
		Forme* stockageTmp = dessins[i];
		dessins[i] = dessins[(i-1)];
		dessins[(i-1)] = stockageTmp;
	}

}

//-------------------------------------------
void Dessin::SendFrontVector(int i)
//-------------------------------------------
{

	if((i+1) < dessins.size()){
		Forme* stockageTmp = dessins[i];
		dessins[i] = dessins[(i+1)];
		dessins[(i+1)] = stockageTmp;
	}

}
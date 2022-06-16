#include <iostream>
#include <cstdlib>
#include <cmath> // pour sqrt

using namespace std;

#include "Forme.h"
#include "Rectangle.h"
#include "Cercle.h"
#include "Triangle.h"

int main()
{
    // test des 4 big four :
    cout << "******** Test des 4 big four de Forme\n";
    Forme f1;
    Forme f2(f1);
    f2 = f1;
    f1.SetLabel("forme1");
    cout << f1.GetLabel() << endl;
    cout << endl;

    // test de la création du cercle :
    cout << "******** Test de creation du cercle\n";
    Cercle c1(Point(100, 100), 10, "cercle1");
    cout << "label du cercle : " << c1.GetLabel() << endl;
    cout << endl;

    // test de la bonne copie d?un cercle :
    cout << "******** Test de la bonne copie d?un cercle\n";
    c1.Display();
    Cercle c2(c1);
    cout << "Voici la copie :" << endl;
    c2.Display();
    cout << endl;

    // test de l?affectation d?un cercle :
    cout << "******** Test de l?affectation d?un cercle\n";
    Cercle c3;
    c3 = c1;
    // ou bien c3.operator=(c1);
    // ou bien c3 = c3.operator=(c1);
    cout << "Voici le resultat de l?affectation :" << endl;
    c3.Display();
    cout << endl;

    // test de la création du triangle :
    cout << "******** Test de la creation du triangle\n";
    Triangle t1(Point(0, 0), Point(20, 0), Point(0, 10), "triangle1");
    cout << "label du triangle : " << t1.GetLabel() << endl;
    cout << endl;

    // test de la bonne copie d?un triangle :
    cout << "******** Test de la bonne copie d?un triangle\n";
    t1.Display();
    Triangle t2(t1);
    cout << "Voici la copie :" << endl;
    t2.Display();
    cout << endl;

    // test de l?affectation d?un triangle :
    cout << "******** Test de l?affectation d?un triangle\n";
    Triangle t3;
    t3 = t1;
    cout << "Voici le resultat de l?affectation :" << endl;
    t3.Display();
    cout << endl;

    // test Display
    Rectangle r1( 0, 0, 100, 200, "r1" );
    cout << "******** Test du Display de differents objets\n";
    f1.Display();
    c1.Display();
    c2.Display();
    t1.Display();
    r1.Display();
    cout << endl;

    // test Surface
    cout << "******** Test de la surface\n";
    cout << "Surface f1= " << f1.Surface() << endl;
    cout << "Surface c1= " << c1.Surface() << endl;
    cout << "Surface t1= " << t1.Surface() << endl;
    cout << endl;

    return EXIT_SUCCESS;
}

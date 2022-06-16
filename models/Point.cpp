#include <iostream>
#include <cstdlib>
#include <cmath> // pour sqrt

#include "Point.h"

using namespace std;

//-------------------------------------------
Point::Point()
//-------------------------------------------
{
    cout << "*** " << __func__ << " ***\n",
    m_x = m_y = 0;
    m_pointCount++;
}

//-------------------------------------------
Point::Point(int x, int y)
//-------------------------------------------
{
    cout << "*** " << __func__ << " ***\n",
    m_x = x;
    m_y = y;
    m_pointCount++;
}

//-------------------------------------------
Point::Point(int z)
//-------------------------------------------
{
    cout << "*** " << __func__ << " ***\n",
    m_x = m_y = z;
    m_pointCount++;
}

//-------------------------------------------
Point::~Point()
//-------------------------------------------
{
    cout << "*** " << __func__ << " ***\n";
    m_pointCount--;
}

//-------------------------------------------
void Point::Move(int dX, int dY)
//-------------------------------------------
{
    m_x += dX;
    m_y += dY;
}

//-------------------------------------------
void Point::Display() const
//-------------------------------------------
{
    cout << "(" << m_x << "," << m_y << ")";
}

//-------------------------------------------
bool Point::XEgalY() const
//-------------------------------------------
{
    return (m_x == m_y) ? true : false;
}

//-------------------------------------------
int Point::GetX() const
//-------------------------------------------
{
    return m_x;
}

//-------------------------------------------
int Point::GetY() const
//-------------------------------------------
{
    return m_y;
}

//-------------------------------------------
void Point::SetX(int x)
//-------------------------------------------
{
    m_x = x;
}

//-------------------------------------------
void Point::SetY(int y)
//-------------------------------------------
{
    m_y = y;
}

//-------------------------------------------
int Point::GetPointCount()
//-------------------------------------------
{
    return m_pointCount;
}

//-------------------------------------------
float Point::Distance(const Point *p) const
//-------------------------------------------
// théorème de pythagore :
// dans un triangle rectangle, le carré de la longueur de l'hypoténuse
// est égal à la somme des carrés des longueurs des deux autres c^otés
{
    return sqrt((m_x - p->m_x) * (m_x - p->m_x) + (m_y - p->m_y) * (m_y - p->m_y));
}

//-------------------------------------------
float Point::Distance(const Point &p) const
// identique à float Point::Distance(Point p)
// remarque : on ne peut pas en plus surcharger avec la méthode
// float Point::Distance(Point p)
// car il y aurait ambiguité au niveau de l?appel :
// dans les 2 cas, le param`etre passé serait de type Point,
// ce qui ne permet pas au compilateur (ni à l(^etre humain)
// de savoir quelle version de la méthode appeler.
//-------------------------------------------
{
    return sqrt((m_x - p.m_x) * (m_x - p.m_x) + (m_y - p.m_y) * (m_y - p.m_y));
}


// Déclaration pour réserver l'espace mémoire de l'attribut statique
// static
int Point::m_pointCount = 0;    // Ici, on ne met pas static

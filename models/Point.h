#ifndef __POINT_H__
#define __POINT_H__

//-------------------------------------------
class Point
//-------------------------------------------
{
public:                        // interface publique de la classe
    Point();                   // constructeur par défaut
    Point(int x, int y);       // constructeur
    Point(int z);              // constructeur (x = y)
    ~Point();                  // destructeur
    void Move(int dX, int dY); // bouge le point

    // Setters
    void SetX(int x);
    void SetY(int y);

    // Getters
    int GetX() const;
    int GetY() const;

    // Méthodes const (qui ne modifie pas l'objet)
    void Display() const;      // affiche les coordonnées du point
    bool XEgalY() const;
    float Distance(const Point &p) const;
    float Distance(const Point *p) const;

    // Méthode statique
    static int GetPointCount(); // retourne le nombre de point

private:                        // invisible à l?utilisateur de la classe
    int m_x;                    // les coordonnées
    int m_y;                    // du point

    // Attribut statique
    static int m_pointCount;    // donnée commune à tous les objets
};

#endif // __POINT_H__ : retour à la ligne obligatoire pour certains compilateurs

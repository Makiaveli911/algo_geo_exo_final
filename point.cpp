#include "point.h"

// renvoie 1, -1 ou 0 selon que le point auquel la m�thode est appliqu�e est
// � gauche de, � droite de, ou sur la droite (ab) orient�e de a vers b.
int Point::aGauche(const Point &a, const Point &b) const
{
	int calcule=(b.x() - a.x()) * (this->y() -a.y()) - (this->x() - a.x()) * (b.y() - a.y());
	if(calcule>0) {
		return 1;
	} else if (calcule<0) {
		return -1;
	}else {
		return 0;
	}
}
// renvoie 1, -1 ou 0 selon que le point auquel la méthode est appliquée est
// au-dessus de, en-dessous de, ou sur la droite (ab) orientée de a vers b.
int Point::dansCercle(const Point& a, const Point& b, const Point& c) const
{
    // 1) On calcule les coordonnées "centrées" (dx, dy) pour a, b, c
    //    par rapport au point this->(x(), y()).
    long long Ax = a.x() - x();
    long long Ay = a.y() - y();
    long long Bx = b.x() - x();
    long long By = b.y() - y();
    long long Cx = c.x() - x();
    long long Cy = c.y() - y();

    // 2) On calcule les carrés des distances
    long long A2 = Ax * Ax + Ay * Ay; // distance au carré entre this et a
    long long B2 = Bx * Bx + By * By; // entre this et b
    long long C2 = Cx * Cx + Cy * Cy; // entre this et c

    // 3) Déterminant 3x3 (Règle de Sarrus) :
    //    | Ax  Ay  A2 |
    //    | Bx  By  B2 |
    //    | Cx  Cy  C2 |
    //
    //    On déploie en longs longs pour éviter tout overflow int.
    long long det =
        (Ax * By * C2)
        + (Ay * B2 * Cx)
        + (A2 * Bx * Cy)
        - (A2 * By * Cx)
        - (Ay * Bx * C2)
        - (Ax * B2 * Cy);

    // 4) Signe du déterminant
    if (det > 0)  return  1; // *this est à l'intérieur du cercle
    else if (det < 0)  return -1; // *this est à l'extérieur
    else               return  0; // *this est exactement sur le cercle
}


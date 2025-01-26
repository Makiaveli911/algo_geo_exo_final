#include "point.h"
#include <corecrt_math.h>

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
int Point::dansCercle(const Point& a, const Point& b, const Point& c) const {
	// Calcul de la matrice 3x3
	const long mA1 = a.x() - this->x();
	const long mA2 = a.y() - this->y();
	const long mA3 = pow(a.x() - this->x(), 2) + pow(a.y() - this->y(), 2);
	const long mB1 = b.x() - this->x();
	const long mB2 = b.y() - this->y();
	const long mB3 = pow(b.x() - this->x(), 2) + pow(b.y() - this->y(), 2);
	const long mC1 = c.x() - this->x();
	const long mC2 = c.y() - this->y();
	const long mC3 = pow(c.x() - this->x(), 2) + pow(c.y() - this->y(), 2);

	// On utilise la règle de Sarrus pour calculer le déterminant
	const long mResult = (mA1 * mB2 * mC3)
		- (mA1 * mB3 * mC2)
		+ (mA2 * mB3 * mC1)
		- (mA2 * mB1 * mC3)
		+ (mA3 * mB1 * mC2)
		- (mA3 * mB2 * mC1);

	if (mResult == 0) {
		return 0;
	}
	return mResult > 0 ? 1 : -1;
}


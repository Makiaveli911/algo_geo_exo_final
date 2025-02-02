#ifndef CARTE_H
#define CARTE_H

#include <vector>
#include "point.h"

using namespace std;

class DemiCote;

class Sommet
{
	friend class Carte;
	friend class DemiCote;

public:
	// Renvoie les coordonn�es du sommet
    Point getPoint() const {return point;}

    // Renvoie un demi-c�t� issu du sommet
    DemiCote* getDemiCote() const {return demiCote;}

    // Renvoie l'index du sommet
    int index() const {return d_index;}

	int objIndex() const { return d_objIndex; }

	void setObjIndex(int index) { d_objIndex = index; }

private:

	// Construit un sommet dont les coordonn�es sont celles de p,
	// � l'extr�mit� du demi-c�t� demiCote et dont l'index est index
	Sommet(const Point& p, DemiCote* demiCote, int index)
		: point(p), demiCote{ demiCote }, d_index{ index }, d_objIndex{ 0 } {};

	// Destructeur de sommet priv�
	~Sommet() = default;

	Point point;
	DemiCote* demiCote;   // l'un des demi-c�t�s issus du sommet
	int d_index;  // la position du sommet dans le tableau d_tabSommets
	int d_objIndex; // index pour la création d'obj recupere l'index
};

class DemiCote
{
	friend class Carte;

public:

    // Renvoie l'adresse du demi-c�t� suivant dans le sens trigonom�trique
	DemiCote* suivant() const {return demiCoteSuivant;}

    // Renvoie l'adresse du demi-c�t� precedent dans le sens trigonom�trique
	DemiCote* precedent() const {return demiCotePrecedent;}

    // Renvoie l'adresse du demi-c�t� oppos�
	DemiCote* oppose() const {return demiCoteOppose;}

	// Renvoie le sommet dont est issu le demi-c�t�
    Sommet* sommet() const {return demiCoteSommet;}

	// Renvoie les coordonn�es du sommet dont est issu le demi-c�t�
    Point point() const {return demiCoteSommet->point;}

	// Renvoie l'index du demi-c�t�
    int index() const {return demiCoteIndex;}

    // Renvoie la marque du demi-c�t�
	int marque() const {return demiCoteMarque;}

    // Met la marque du demi-c�t� � m
	void changeMarque(int m) const {const_cast<int&>(demiCoteMarque) = m;}

private:

	// Construit un demi-c�t� dont suivant est le demi-c�t� suivant,
	// precedent est le demi-c�t� pr�c�dent, oppose est le demi-c�t� oppos�,
	// sommet est le sommet dont il est issu et index est l'index
	DemiCote(DemiCote* suivant, DemiCote* precedent, DemiCote* oppose, Sommet* sommet, int index)
			 : demiCoteSuivant{suivant}, demiCotePrecedent{precedent}, demiCoteOppose{oppose},
			 demiCoteSommet{sommet}, demiCoteIndex{index}, demiCoteMarque{0} {};

	// Destructeur de demi-c�t� priv�
	~DemiCote() = default;


	DemiCote* demiCoteSuivant;
	DemiCote* demiCotePrecedent;
	DemiCote* demiCoteOppose;
	Sommet* demiCoteSommet;
	int demiCoteIndex;       // la position du demi-c�t� dans le tableau d_tabDemiCote
	int demiCoteMarque;	   // la marque du demi-c�t� (0 par d�faut)
};

class Carte
{
public:

    // Constructeur par d�faut
    Carte() : demiCoteParticulier{nullptr} {}

	// Destructeur
	~Carte();

    // Renvoie le nombre de sommets de la carte
	int tailleTableauSommets() const {return tableauSommets.size();}

    // Renvoie l'adresse du sommet d'index i (0 <= i < nbSommets())
	Sommet* getTableauSommet(int i) const	{return tableauSommets[i];}

    // Renvoie le nombre de demi-c�t�s de la carte
	int tailleTableauDemiCotes() const {return tableauDemiCote.size();}

    // Renvoie l'adresse du demi-c�t� d'index i (0 <= i < nbDemiCotes())
	DemiCote* getTableauDemiCote(int i) const	{return tableauDemiCote[i];}

	// Renvoie l'adresse du demi-c�t� particulier de la carte
	DemiCote* getDemiCoteParticulier() const {return demiCoteParticulier;}

	// Modifie le demi-c�t� particulier de la carte
	void changeDemiCoteParticulier(DemiCote* particulier)
	{demiCoteParticulier = particulier;}

    // Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2
    // dont precedent1 et precedent2 seront les demi-c�t�s pr�c�dents respectifs.
    // On suppose precedent1 et precedent2 d�j� pr�sents dans la carte.
    // Renvoie l'adresse de dc1.
	DemiCote* ajouteCote(DemiCote* precedent1, DemiCote* precedent2);

    // Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2.
    // precedent1 sera le demi-c�t� pr�c�dent de dc1. dc2 sera issu d�un
    // nouveau sommet (� cr�er) dont les coordonn�es sont celles du point p2.
    // On suppose precedent1 d�j� pr�sent dans la carte.
    // Renvoie l'adresse de dc1.
	DemiCote* ajouteCote(DemiCote* precedent1, const Point& p2);

    // Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2.
    // precedent2 sera le demi-c�t� pr�c�dent de dc2. dc1 sera issu d�un
    // nouveau sommet (� cr�er) dont les coordonn�es sont celles du point p1.
    // On suppose precedent2 d�j� pr�sent dans la carte.
    // Renvoie l'adresse de dc1.
	DemiCote* ajouteCote(const Point& p1, DemiCote* precedent2);

    // Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2.
    // dc1 et dc2 seront issus de deux nouveaux sommets (� cr�er) dont les
	// coordonn�es sont celles des points p1 et p2 respectivement.
    // Renvoie l'adresse de dc1.
	DemiCote* ajouteCote(const Point& p1, const Point& p2);

	void flip(DemiCote* d);
private:

	// Ajoute un nouveau demi-c�t� dans la carte dont precedent sera le demi-c�t�
	// 	pr�c�dent et oppose sera le demi-c�t� oppos�.
	// On suppose que le demi-c�t� precedent est d�j� pr�sent dans la carte.
	// Le demi-c�t� oppose est soit d�j� pr�sent dans la carte soit nul (valeur
	// par d�faut).
	// Renvoie l�adresse du nouveau demi-c�t�.
	DemiCote* ajouteDemiCote(DemiCote* precedent, DemiCote* oppose=nullptr);

	// Ajoute un nouveau demi-c�t� dans la carte qui sera issu d�un nouveau
	// sommet (� cr�er) dont les coordonn�es sont celles du point p.
	// oppose sera le demi-c�t� oppos� du nouveau demi-c�t�.
	// oppose est soit d�j� pr�sent dans la carte soit nul (valeur par d�faut).
	// Renvoie l�adresse du nouveau demi-c�t�.
	DemiCote* ajouteDemiCote(const Point &p, DemiCote* oppose=nullptr);

    


    vector<Sommet*> tableauSommets;       // tableau des sommets
	vector<DemiCote*> tableauDemiCote;   // tableau des demi-c�t�s
	DemiCote* demiCoteParticulier;    // demi-c�t� particulier (nul par d�faut)
};

#endif

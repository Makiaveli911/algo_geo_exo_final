#include "affichage.h"
#include "point.h"
#include "carte.h"
#include "graphics.h"
#include <iostream>

// trace un segment entre deux points a et b
void segment(const Point &a, const Point &b)
{
}

void trace(const Carte& C)
{
    // Initialiser les paramètres pour la fenêtre graphique
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Obtenir la hauteur de la fenêtre graphique
    int height = getmaxy();

    // Dessiner les demi-côtés
    for (int i = 0; i < C.tailleTableauDemiCotes(); i++)
    {
        // Obtenir le demi-côté courant
        DemiCote* demiCoteCourant = C.getTableauDemiCote(i);

        // Vérifier que le demi-côté a un opposé
        if (demiCoteCourant->oppose() != nullptr)
        {
            // Obtenir les coordonnées des sommets
            Point p1 = demiCoteCourant->point();
            Point p2 = demiCoteCourant->oppose()->point();

            // Tracer une ligne entre p1 et p2 et inversion de l'axe verticale
            line(p1.x(), height -p1.y(), p2.x(), height -p2.y());
        }
    }

    // Dessiner les sommets
    for (int i = 0; i < C.tailleTableauSommets(); i++)
    {
        // Obtenir le sommet courant
        Sommet* sommet = C.getTableauSommet(i);

        // Obtenir les coordonnées du sommet
        Point p = sommet->getPoint();

        //inversion de l'axe vertical
        int x = p.x();
        int y = height - p.y();
        // Dessiner un petit cercle pour représenter le sommet
        setcolor(RED);
        circle(x, y, 5);
        floodfill(x, y, RED);
    }

    // Attendre une entrée de l'utilisateur pour fermer la fenêtre
    std::cout << "Appuyez sur une touche pour quitter..." << std::endl;
    getch();
    closegraph(); // Fermer la fenêtre graphique
}


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
    // Initialiser les paramètres pour la fenêtre graphique en mode plein écran
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    setgraphmode(getmaxmode()); // Met en plein écran

    int width = 1920;  // Largeur max de la fenêtre
    int height = 1000; // Hauteur max de la fenêtre

    std::cout << "Resolution: " << width << "x" << height << std::endl;

    // Tracer les demi-côtés
    for (int i = 0; i < C.tailleTableauDemiCotes(); i++)
    {
        DemiCote* demiCoteCourant = C.getTableauDemiCote(i);

        if (demiCoteCourant->oppose() != nullptr)
        {
            Point p1 = demiCoteCourant->point();
            Point p2 = demiCoteCourant->oppose()->point();

            // Adapter Y pour que (0,0) soit en bas à gauche
            int x1 = p1.x();
            int y1 = height - p1.y();
            int x2 = p2.x();
            int y2 = height - p2.y();

            line(x1, y1, x2, y2);
        }
    }

    // Dessiner les sommets
    for (int i = 0; i < C.tailleTableauSommets(); i++)
    {
        Sommet* sommet = C.getTableauSommet(i);
        Point p = sommet->getPoint();

        int x = p.x();
        int y = height - p.y(); // Correction de l'axe Y

        setcolor(RED);
        circle(x, y, 5);
        floodfill(x, y, RED);
    }

    // Attendre une entrée utilisateur avant de fermer
    std::cout << "Appuyez sur une touche pour quitter..." << std::endl;
    getch();
    closegraph(); // Fermer la fenêtre graphique
}


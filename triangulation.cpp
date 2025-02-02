//
// Created by chaid on 13/12/2024.
//
#include "carte.h"
#include "triangulation.h"
#include <algorithm> // POUR LE SORT
#include <stdexcept>

#include "triangulation.h"
#include <algorithm> // pour std::sort
#include <stdexcept>
#include <stack>
#include <vector>
#include <iostream>

// Implémentation de la fonction triangulation
void triangulation(std::vector<Point>& T, Carte& C) {
    // Étape 1 : Trier les points par abscisses croissantes
    std::sort(T.begin(), T.end(), [](const Point& a, const Point& b) {
        return (a.x() < b.x() || (a.x() == b.x() && a.y() < b.y()));
        });

    // Vérification
    if (T.size() < 2) {
        throw std::invalid_argument("L'ensemble de points doit contenir au moins deux points !");
    }

    // Étape 2 : Construire un premier segment de base entre les deux premiers points
    DemiCote* demiCoteReference = C.ajouteCote(T[0], T[1]);
    C.changeDemiCoteParticulier(demiCoteReference);

    // Étape 3 : Ajouter les points restants à l'enveloppe convexe
    for (size_t i = 2; i < T.size(); ++i) {
        Point pointAAjouter = T[i];

        DemiCote* demiCoteReference2 = C.ajouteCote(pointAAjouter, demiCoteReference);

        // Sens trigonométrique : trouver les côtés à droite du point

        while (pointAAjouter.aGauche(demiCoteReference->point(), demiCoteReference->suivant()->suivant()->oppose()->point()) == -1) {
            demiCoteReference = demiCoteReference->suivant()->suivant()->oppose();
            C.ajouteCote(demiCoteReference, demiCoteReference2);
        }

        demiCoteReference = demiCoteReference2->oppose()->precedent();

        while (pointAAjouter.aGauche(demiCoteReference->oppose()->point(), demiCoteReference->point()) == -1) {
            demiCoteReference = demiCoteReference->oppose()->precedent();
            demiCoteReference2 = C.ajouteCote(demiCoteReference2, demiCoteReference);
        }

        demiCoteReference = demiCoteReference2;

        // Relier le pointAAjouter aux deux sommets valides
        //DemiCote* nouveauDemiCote = C.ajouteCote(sommetReference->oppose(), pointAAjouter);
    };
}

void Carte::flip(DemiCote* d) {
    // On traite le premier demicote
    d->precedent()->demiCoteSuivant = d->suivant();
    d->suivant()->demiCotePrecedent = d->precedent();

    DemiCote* d_initial_oppose = d->precedent()->oppose();
    d->demiCoteSommet = d_initial_oppose->sommet();

    d_initial_oppose->demiCotePrecedent->demiCoteSuivant = d;
    d->demiCotePrecedent = d_initial_oppose->demiCotePrecedent;

    d_initial_oppose->demiCotePrecedent = d;
    d->demiCoteSuivant = d_initial_oppose;

    // On traite son opposé
    DemiCote* d_oppose = d->oppose();
    d_oppose->precedent()->demiCoteSuivant = d_oppose->suivant();
    d_oppose->suivant()->demiCotePrecedent = d_oppose->precedent();

    DemiCote* d_oppose_oppose = d_oppose->precedent()->oppose();
    d_oppose->demiCoteSommet = d_oppose_oppose->sommet();

    d_oppose_oppose->demiCotePrecedent->demiCoteSuivant = d_oppose;
    d_oppose->demiCotePrecedent = d_oppose_oppose->demiCotePrecedent;

    d_oppose_oppose->demiCotePrecedent = d_oppose;
    d_oppose->demiCoteSuivant = d_oppose_oppose;
}
void delaunay(std::vector<Point>& T, Carte& C)
{
    // 1) Construire d'abord une triangulation
    triangulation(T, C);

    if (!C.getDemiCoteParticulier()) {
        std::cout << "Carte vide.\n";
        return;
    }

    // 2) Marquer le bord (on part du demiCoteParticulier qui est sur le "bord")
    // Afficher un message de succès
    std::cout << "Debut marquage des coté sur le bord !" << std::endl;
    DemiCote* start = C.getDemiCoteParticulier();
    DemiCote* courant = start;
    do {
        courant->changeMarque(1); // 1 => bord
        courant->oppose()->changeMarque(1);
        courant = courant->oppose()->suivant();
    } while (courant != start);
    // Afficher un message de succès
    std::cout << "Marquage des bord reussi !" << std::endl;







    // 3) Empiler les autres (non-bord => marque=0)
    // Afficher un message de succès
    std::cout << "creation de la pile !" << std::endl;
    std::stack<DemiCote*> pileATraiter;
    for (int i = 0; i < C.tailleTableauDemiCotes(); i++) {

        DemiCote* demiCoteCourant = C.getTableauDemiCote(i);
        if (demiCoteCourant->marque() != 2) {
            demiCoteCourant->changeMarque(2);        // 2 => "dans la pile"
            demiCoteCourant->oppose()->changeMarque(2);
            pileATraiter.push(demiCoteCourant);
        }
    }

     // 4) Boucle de flips
    while (!pileATraiter.empty())
    {
        DemiCote* traitement = pileATraiter.top();
        pileATraiter.pop();
        // démarquer => 0
        traitement->changeMarque(0);
        traitement->oppose()->changeMarque(0);

        if (traitement->precedent()->oppose()->sommet()->getPoint().dansCercle(
        traitement->point(),
        traitement->suivant()->oppose()->point(),
        traitement->oppose()->point()) < 0){
            for (DemiCote * dc : {traitement->oppose()->precedent(),
            traitement->oppose()->suivant(),
            traitement->precedent(),
            traitement->suivant()}) {
                if (dc->marque() == 0) {
                    dc->changeMarque(2);
                    dc->oppose()->changeMarque(2);
                    pileATraiter.push(dc);
                }
            }
            // flip
            C.flip(traitement);
        }
    }

    // Fin => Delaunay
    std::cout << "Triangulation Delaunay terminee\n";
}
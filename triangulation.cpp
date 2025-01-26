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

        DemiCote* demiCoteReference2 = C.ajouteCote(pointAAjouter,demiCoteReference);

        // Sens trigonométrique : trouver les côtés à droite du point

        auto p1 = demiCoteReference->suivant();
        auto p2 = demiCoteReference->suivant()->suivant();

        while (pointAAjouter.aGauche(demiCoteReference->point(), demiCoteReference->suivant()->suivant()->oppose()->point()) == -1) {
            demiCoteReference = demiCoteReference->suivant()->suivant()->oppose();
            C.ajouteCote(demiCoteReference, demiCoteReference2);
        }

        demiCoteReference = demiCoteReference2->oppose()->precedent();

        while(pointAAjouter.aGauche(demiCoteReference->oppose()->point(), demiCoteReference->point()) == -1) {
            demiCoteReference = demiCoteReference->oppose()->precedent();
            demiCoteReference2 = C.ajouteCote(demiCoteReference2, demiCoteReference);
        }

        demiCoteReference = demiCoteReference2;

        // Relier le pointAAjouter aux deux sommets valides
        //DemiCote* nouveauDemiCote = C.ajouteCote(sommetReference->oppose(), pointAAjouter);
    }
    // Création d'une pile pour stocker les demi-côtés à corriger
    std::stack<DemiCote*> demiCotesACorriger;
    const DemiCote* coteForloop = C.getDemiCoteParticulier();
    do {
        // On marque les demi-côtés de la carte
        coteForloop->changeMarque(1);
        coteForloop->oppose()->changeMarque(1);
        coteForloop = coteForloop->oppose()->suivant();
    } while (coteForloop != C.getDemiCoteParticulier());

    // Parcours des demi-côtes de la carte
    for (int i = 0; i < C.tailleTableauDemiCotes(); i++) {
        DemiCote* toPush = C.getTableauDemiCote(i);
        // Si le demi-côté n'est pas marqué, on la marque et on l'ajoute à la pile pour traitement
        if (toPush->marque() != 1) {
            toPush->changeMarque(1);
            toPush->oppose()->changeMarque(1);
            demiCotesACorriger.push(toPush);
        }
    }

    // On traite les demi-côtes à corriger
    while (!demiCotesACorriger.empty()) {
        // On récupère le premier élément de la pile
        DemiCote* traitement = demiCotesACorriger.top();
        demiCotesACorriger.pop();
        traitement->changeMarque(0);
        traitement->oppose()->changeMarque(0);
        // Si le sommet de la demi-côte précédente est dans le cercle circonscrit de la demi-côte, on effectue un flip
        if (traitement->precedent()->oppose()->sommet()->getPoint().dansCercle(
            traitement->point(),
            traitement->suivant()->oppose()->point(),
            traitement->oppose()->point()) < 0) {
            for (DemiCote* dc : { traitement->oppose()->precedent(),
                                traitement->oppose()->suivant(),
                                traitement->precedent(), traitement->suivant() }) {
                // Si le demi-côté n'est pas marqué, on le marque et on l'ajoute à la pile
                if (dc->marque() == 0) {
                    dc->changeMarque(1);
                    dc->oppose()->changeMarque(1);
                    demiCotesACorriger.push(dc);
                }
            }
            C.flip(traitement);
        }
    }
}
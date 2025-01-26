#include "point.h"
#include "carte.h"
#include "affichage.h"
#include "triangulation.h"
#include <iostream>

int main() {
    try{
    // Initialiser une carte
    Carte carte;

    // Ajouter des points pour les sommets
        Point p1(50, 250);
        Point p2(100, 100);
        Point p3(120, 230);
        Point p4(245, 25);
        Point p5(260, 320);
        Point p6(340, 250);
        Point p7(355, 110);
        Point p8(380, 150);
        Point p9(500, 150);


    // Ajouter ces points dans un vecteur
    std::vector<Point> points = {p1, p2, p3, p4,p5 ,p6,p7, p8 ,p9};
    triangulation(points, carte);

    // Afficher un message de succès
    std::cout << "Triangulation réalisée avec succès !" << std::endl;

    trace(carte);


} catch (const std::exception& e) {
    // Gérer les exceptions
    std::cerr << "Erreur : " << e.what() << std::endl;
}

    return 0;

    }
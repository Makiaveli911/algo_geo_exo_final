#include "point.h"
#include "carte.h"
#include "affichage.h"
#include "triangulation.h"
#include <iostream>
#include <vector>
#include <fstream>    // Pour ifstream
#include <limits>  

int main() {
    try{
//    // Initialiser une carte
//    Carte carte;
//
//    // Ajouter des points pour les sommets
//    Point p1(50, 200);
//    Point p2(300, 20);
//    Point p3(120, 250);
//    Point p4(90, 400);
//    Point p7(450, 370);
//    Point p5(470, 190);
//    Point p6(510, 240);
//
//
//    // Ajouter ces points dans un vecteur
//    std::vector<Point> points = {p1, p2, p3, p4,p5 ,p6,p7};
        std::ifstream file
        ("C:/Users/makia/Documents/exercice a faire/algo_geo_exo4_triangulation_de_delaunay/Hohneck.txt");
        if (!file) {
            std::cout << "Impossible d'ouvrir le fichier !";
            return EXIT_FAILURE;
        }

        // On ignore la première ligne
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        float x, y, z;
        std::vector<Point> points;
        while (file >> x >> y >> z) {
            points.emplace_back(x, y);
        }

    Carte carte;
    delaunay(points, carte);

    // Afficher un message de succès
    std::cout << "Triangulation réalisée avec succès !" << std::endl;
    // On applique ensuite la fonction de Delaunay (tout-en-un)
    trace(carte);


} catch (const std::exception& e) {
    // Gérer les exceptions
    std::cerr << "Erreur : " << e.what() << std::endl;
}

    return 0;

    }
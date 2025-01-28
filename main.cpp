#include "point.h"
#include "carte.h"
#include "affichage.h"
#include "triangulation.h"
#include <iostream>
#include <fstream>

int main() {
    try{
    //    std::ifstream file
    //    ("C:/Users/makia/Documents/exercice a faire/algo_geo_exo_final/Hohneck.txt");
    //    if (!file) {
    //        std::cout << "Impossible d'ouvrir le fichier !";
    //        return EXIT_FAILURE;
    //    }

    //    // On ignore la première ligne
    //    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    //    float x, y, z;
    //    std::vector<Point> points;
    //    while (file >> x >> y >> z) {
    //        points.emplace_back(x, y);
    //    }
    // Initialiser une carte
    Carte carte;

    //// Ajouter des points pour les sommets
    Point p1(10, 4105);
    Point p2(3415, 10);
    Point p3(2435, 835);
    Point p4(2940, 2570);
    Point p5(1865, 1600);
    Point p6(1585, 3090);
    Point p7(1235, 1060);
    Point p8(1385, 1930);
    Point p9(3415, 2845);
    Point p10(2160, 3410);
    Point p11(1510, 3620);
    Point p12(1500, 470);
    Point p13(900, 1255);
    Point p14(3075, 1840);
    Point p15(2330, 270);
    Point p16(3415, 4105);
    Point p17(10, 11);


    //// Ajouter ces points dans un vecteur
    std::vector<Point> points = {p1, p2, p3, p4,p5 ,p6,p7, p8 ,p9,p10,p11,p12,p13,p14,p15,p16,p17};
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
//
// Created by chaid on 13/12/2024.
//
#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <vector>
#include "carte.h"
#include "point.h"

    // Déclare la fonction de triangulation
    void triangulation(std::vector<Point>& T, Carte& C);
    void delaunay(std::vector<Point>& T, Carte& C);



#endif //TRIANGULATION_H

#include "createObj.h"
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <tuple>
#include "carte.h"

void exportOBJ(const Carte& C, const std::string& file) {
    // Cr�ation ou ouverture du fichier avec le nom pass� en param�tre
    std::ofstream objFile(file);
    if (!objFile.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << file << std::endl;
        return;
    }

    // Optionnel : on ajoute la r�f�rence au fichier MTL pour les textures
    objFile << "mtllib texture.mtl\n";

    // �criture des sommets (vertices)
    for (int i = 0; i < C.tailleTableauSommets(); ++i) {
        Sommet* sommet = C.getTableauSommet(i);
        objFile << "v " << sommet->getPoint().x() << " "
            << sommet->getPoint().y() << " "
            << sommet->getPoint().z() << "\n";

        // Mise � jour de l'index du sommet dans le fichier OBJ (les indices OBJ commencent � 1)
        sommet->setObjIndex(i + 1);
    }

    // Cr�ation des faces triangulaires
    std::set<std::tuple<Sommet*, Sommet*, Sommet*>> processed;
    std::vector<std::tuple<Sommet*, Sommet*, Sommet*>> triangles;

    for (int i = 0; i < C.tailleTableauDemiCotes(); ++i) {
        DemiCote* demiCote = C.getTableauDemiCote(i); // Assurez-vous que cette m�thode existe
        if (!demiCote) continue;
        DemiCote* oppose = demiCote->oppose();
        if (!oppose) continue;
        DemiCote* oppose_precedent = oppose->precedent()->oppose();
        if (!oppose_precedent) continue;

        // Cr�ation du tuple repr�sentant le triangle
        // Un tuple est une structure de donn�es qui peut contenir plusieurs valeurs de 
        // types (potentiellement diff�rents) regroup�es en une seule entit�.
        auto triangle = std::make_tuple(
            demiCote->sommet(),
            oppose->sommet(),
            oppose_precedent->sommet()
        );

        // On v�rifie que ce triangle n'a pas d�j� �t� trait�
        //processed c'est un conteneur de type std::set
        //Si l'�l�ment est d�j� pr�sent dans le set, l'insertion �chouera
        if (processed.insert(triangle).second) {
            triangles.push_back(triangle);
        }
    }

    for (const auto& triangle : triangles) {
        // On r�cup�re les altitudes (z) des sommets du triangle
        const float z1 = std::get<0>(triangle)->getPoint().z();
        const float z2 = std::get<1>(triangle)->getPoint().z();
        const float z3 = std::get<2>(triangle)->getPoint().z();

        // Calcul de l'altitude moyenne des trois sommets
        const float z_moyenne = (z1 + z2 + z3) / 3.0;

        // Attribution des mat�riaux en fonction des plages d'altitudes
        if (z_moyenne <= 780) {
            objFile << "usemtl BleuNuit\n";
        }
        else if (z_moyenne <= 820) {
            objFile << "usemtl BleuProfond\n";
        }
        else if (z_moyenne <= 860) {
            objFile << "usemtl BleuClair\n";
        }
        else if (z_moyenne <= 900) {
            objFile << "usemtl Turquoise\n";
        }
        else if (z_moyenne <= 940) {
            objFile << "usemtl VertTurquoise\n";
        }
        else if (z_moyenne <= 980) {
            objFile << "usemtl VertVif\n";
        }
        else if (z_moyenne <= 1020) {
            objFile << "usemtl JauneVert\n";
        }
        else if (z_moyenne <= 1060) {
            objFile << "usemtl JauneVif\n";
        }
        else if (z_moyenne <= 1100) {
            objFile << "usemtl OrangeClair\n";
        }
        else if (z_moyenne <= 1140) {
            objFile << "usemtl OrangeVif\n";
        }
        else if (z_moyenne <= 1180) {
            objFile << "usemtl RougeClair\n";
        }
        else if (z_moyenne <= 1220) {
            objFile << "usemtl RougeInter1\n";
        }
        else if (z_moyenne <= 1260) {
            objFile << "usemtl RougeInter2\n";
        }
        else if (z_moyenne <= 1320) {
            objFile << "usemtl RougeVif\n";
        }
        else {
            objFile << "usemtl RougeUltraVif\n";
        }

        // �criture de la face
        objFile << "f " << std::get<0>(triangle)->objIndex() << " "
            << std::get<1>(triangle)->objIndex() << " "
            << std::get<2>(triangle)->objIndex() << "\n";
    }


    objFile.close();
    std::cout << "Fichier OBJ cr�� : " << file << std::endl;
}

#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <fstream>
#include "Sommet.h"
#include "Arete.h"
#include <string>
#include <vector>

class Graphe
{
    private :
        std::vector<Sommet*> m_sommets;
        std::vector<Arete*> m_aretes;
        std::vector<Sommet*> m_sommetsPrim;
        std::vector<Arete*> m_arretesPrim;


    public :
        //faire prim
        Graphe(std::string nomFichierCoord, std::string nomFichierPoids);
        Graphe();
        void algoPrim(int& indice);
        ~Graphe();




};


#endif // GRAPHE_H_INCLUDED

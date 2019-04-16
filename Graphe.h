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
        std::vector<Arete*> m_aretesPrim1;
        std::vector<Arete*> m_aretesPrim2;
        int m_ordre;
        int m_poids1Tot1;           // Total du poids 1 pour Prim poids 1
        int m_poids2Tot1;           // Total du poids 2 pour Prim poids 1
        int m_poids1Tot2;           // Total du poids 1 pour Prim poids 2
        int m_poids2Tot2;           // Total du poids 2 pour Prim poids 2


    public :
        //faire prim
        Graphe(std::string nomFichierCoord, std::string nomFichierPoids);
        Graphe();
        void algoPrim();
        void algoPareto();
        ~Graphe();

};


#endif // GRAPHE_H_INCLUDED

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

    public :
        //faire prim
        Graphe(std::string nomFichierCoord, std::string nomFichierPoids);
        Graphe();
        std::vector<Arete*> algoPrim();
        void algoPareto();
        ~Graphe();

};


#endif // GRAPHE_H_INCLUDED

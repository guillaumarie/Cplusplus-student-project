#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <fstream>
#include "Sommet.h"
#include "Arete.h"
#include <string>
#include <vector>
#include <allegro.h>
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
        void algoPrim();
        ~Graphe();
        void dessinerGraphe();
        void dessinerPrim1();
        void dessinerPrim2();


};


#endif // GRAPHE_H_INCLUDED

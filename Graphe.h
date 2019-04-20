#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <fstream>
#include "Sommet.h"
#include "Arete.h"
#include <string>
#include <vector>
#include <allegro.h>
#include <algorithm>
#include <utility>
#include <bits/stdc++.h>


class Graphe
{
    private :
        std::vector<Sommet*> m_sommets;
        std::vector<Arete*> m_aretes;
        std::vector<Arete*> m_aretesPrim1;
        std::vector<Arete*> m_aretesPrim2;
        std::vector<std::vector<float>> m_frontierePareto;
        std::vector<std::vector<float>> m_nuagePoints;
        int m_ordre;
        float m_poids1Tot1;           // Total du poids 1 pour Prim poids 1
        float m_poids2Tot1;           // Total du poids 2 pour Prim poids 1
        float m_poids1Tot2;           // Total du poids 1 pour Prim poids 2
        float m_poids2Tot2;           // Total du poids 2 pour Prim poids 2


    public :
        Graphe(std::string nomFichierCoord, std::string nomFichierPoids);
        Graphe();
        void algoPrim();
        void algoPareto();
        void dessinerGraphe();
        void dessinerPrim1();
       void dessinerPrim2();
        std::vector<std::vector<float>> getFrontier(){return m_frontierePareto;}
        std::vector<std::vector<float>> getNuage(){return m_nuagePoints;}
        void dessinerPareto(std:: vector<std::vector<float>> m_frontierePareto,std::vector<std::vector<float>> m_nuagePoints);
        std::vector<Arete*> getm_Arete();
        ~Graphe();


};


#endif // GRAPHE_H_INCLUDED

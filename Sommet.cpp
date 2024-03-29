#include "Sommet.h"

//constructeur
Sommet::Sommet(int id, double x ,double y):m_marque1{false},m_marque2{false},m_id{id},m_x{x},m_y{y}
{
}

///------------------------------------------------------------------

Sommet::~Sommet()
{}

///----------------------------------------------------------------------------

void Sommet::ajouterVoisin(const Sommet* voisin){
    m_voisins.push_back(voisin);
}

///----------------------------------------------------------------------------

int Sommet::verifierCC() const
{
    std::unordered_set<const Sommet*> decouvert;
    std::stack<const Sommet*> pile;
    std::vector<const Sommet*> voisins;
    int cc = 1;

    // parcours DFS
    pile.push(this); //on ajoute en premier � la pile le sommet de d�part
    decouvert.insert(this); //on le marque comme explor�
    while( pile.empty() != 1 ) //tant que la pile n'est pas vide
    {
        const Sommet* s;
        s = pile.top();           // lecture de l'�l�ment du haut de la pile
        pile.pop();                 // on enleve le sommet s de la pile apres l'avoir marqu� = l'avoir ajout� dans le unordered_map
        voisins = s->getVoisins();
        for(auto v:voisins)
        {
            if(decouvert.count(v)==0)       //si le voisin n'est pas d�couvert
            {
                pile.push(v);           //alors on ajoute tous les voisins � la pile
                decouvert.insert(v);       //on le marque comme explor�
                ++cc;
            }
        }
    }
    return cc;
}


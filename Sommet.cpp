#include "Sommet.h"

//constructeur
Sommet::Sommet(int id, double x ,double y):m_marque1{false},m_marque2{false},m_id{id},m_x{x},m_y{y}
{
}

///------------------------------------------------------------------

Sommet::~Sommet()
{}

///----------------------------------------------------------------------------

void Sommet::ajouterVoisin(Sommet* voisin){
    m_voisins.push_back(voisin);
}

///----------------------------------------------------------------------------

/// Méthode rechercherCC inspiré du TP2 (réalisé avec Martin Puyou-Lascassies)

int Sommet::verifierCC()
{
    std::unordered_set<Sommet*> decouvert;
    std::stack<Sommet*> pile;
    std::vector<Sommet*> voisins;
    int cc = 1;

    // parcours DFS
    pile.push(this); //on ajoute en premier à la pile le sommet de départ
    decouvert.insert(this); //on le marque comme exploré
    while( pile.empty() != 1 ) //tant que la pile n'est pas vide
    {
        Sommet* s;
        s->setVoisins();
        s = pile.top();           // lecture de l'élément du haut de la pile
        pile.pop();                 // on enleve le sommet s de la pile apres l'avoir marqué = l'avoir ajouté dans le unordered_map
        voisins = s->getVoisins();
        for(auto v:voisins)
        {
            if(decouvert.count(v)==0)       //si le voisin n'est pas découvert
            {
                pile.push(v);           //alors on ajoute tous les voisins à la pile
                decouvert.insert(v);       //on le marque comme exploré
                ++cc;
            }
        }
    }
    return cc;
}


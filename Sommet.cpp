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

/// M�thode rechercherCC inspir� du TP2 (r�alis� avec Martin Puyou-Lascassies)

int Sommet::verifierCC()
{
    std::unordered_set<Sommet*> decouvert;
    std::queue<Sommet*> file;
    std::vector<Sommet*> voisins;
    int cc = 1;

    // parcours BFS mais sans return d'un l_pred : -------------------------------------------------------------
    file.push(this); //on ajoute en premier � la file le sommet de d�part
    decouvert.insert(this); //on le marque comme explor�
    while( file.empty() != 1 ) //tant que la file n'est pas vide
    {
        Sommet* s;
        s->setVoisins();
        s = file.front();           // lecture du premier �l�ment de la file
        file.pop();                 // on enleve le sommet s de la file apres l'avoir marqu� = l'avoir ajout� dans le unordered_map
        voisins = s->getVoisins();
        for(auto v:voisins)
        {
            if(decouvert.count(v)==0) //si le voisin n'est pas d�couvert
            {
                file.push(v);           //alors on ajoute tous les voisins � la file
                decouvert.insert(v);       //on le marque comme explor�
                ++cc;
            }
        }
    }
    return cc;
}


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
    std::unordered_set<const Sommet*> decouvert;
    std::queue<Sommet*> file;
    std::vector<Sommet*> voisins;
    int cc = 1;

    // parcours BFS mais sans return d'un l_pred : -------------------------------------------------------------
    file.push(this); //on ajoute en premier à la file le sommet de départ
    decouvert.insert(this); //on le marque comme exploré
    while( file.empty() != 1 ) //tant que la file n'est pas vide
    {
        Sommet* s;
        s->setVoisins();
        s = file.front();           // lecture du premier élément de la file
        file.pop();                 // on enleve le sommet s de la file apres l'avoir marqué = l'avoir ajouté dans le unordered_map
        voisins = s->getVoisins();
        for(size_t i = 0; i<voisins.size(); i++)
        {
            if((decouvert.count(voisins[i]))==0) //si le voisin n'est pas découvert
            {
                file.push(voisins[i]);           //alors on ajoute tous les voisins à la file
                decouvert.insert(voisins[i]);       //on le marque comme exploré
                ++cc;
            }
        }
    }
    return cc;
}

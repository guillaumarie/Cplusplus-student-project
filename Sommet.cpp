#include "Sommet.h"

//constructeur
Sommet::Sommet(int id, double x ,double y):m_marque1{false},m_marque2{false},m_id{id},m_x{x},m_y{y}
{
}

///------------------------------------------------------------------

Sommet::~Sommet()
{}

///----------------------------------------------------------------------------

/// Méthode rechercherCC inspiré du TP2 (réalisé avec Martin Puyou-Lascassies)

std::unordered_set<std::string> Sommet::rechercherCC() const
{
    std::unordered_set<const Sommet*> decouvert;
    std::queue<const Sommet*> file;
    std::vector<const Sommet*> voisins;
    std::unordered_set<std::string> cc;

    // parcours BFS mais sans return d'un l_pred : -------------------------------------------------------------
    file.push(this); //on ajoute en premier à la file le sommet de départ
    decouvert.insert(this); //on le marque comme exploré
    cc.insert(this->m_id);
    while( file.empty() != 1 ) //tant que la file n'est pas vide
    {
        const Sommet* s;
        s = file.front(); // lecture du premie r élément de la file
        file.pop(); // on enleve le sommet s de la file apres l'avoir marqué = l'avoir ajouté dans le unordered_map
        voisins = s->geterVoisins();
        for(size_t i = 0; i<voisins.size(); i++)
        {
            if((decouvert.count(voisins[i]))==0) //si le voisin n'est pas découvert
            {
                file.push(voisins[i]); //alors on ajoute tous les voisins à la file
                decouvert.insert(voisins[i]); //on le marque comme exploré
                cc.insert( voisins[i]->geterId() );
            }
        }
    }

    return cc;

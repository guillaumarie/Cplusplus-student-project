#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <queue>
#include <vector>
#include <unordered_set>

class Sommet
{

    private : //attributs
        bool m_marque1; //sommet marqué = ajouté dans l'arbre couvrant par rapport au poids 1
        bool m_marque2;
        int m_id;
        double m_x;
        double m_y;
        std::vector<Sommet*> m_voisins; // tableau contenant les sommets voisins


    public : //méthodes
        Sommet(int id, double x, double y);
        void ajouterVoisin(Sommet*);
        //int getId() const {return m_id;};
        int getX(){return m_x;};
        int getY(){return m_y;};
        int getMarque1(){return m_marque1;};        // Marque pour le poids 1
        int getMarque2(){return m_marque2;};        // Marque pour le poids 2
        void marquer1(){m_marque1=true;};
        void marquer2(){m_marque2=true;};
        int verifierCC();
        std::vector<Sommet*> getVoisins() {return m_voisins;};
        void setVoisins() {m_voisins.clear();};
        ~Sommet();

};
#endif // SOMMET_H_INCLUDED



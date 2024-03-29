#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <stack>
#include <vector>
#include <unordered_set>

class Sommet
{

    private : //attributs
        bool m_marque1; //sommet marqu� = ajout� dans l'arbre couvrant par rapport au poids 1
        bool m_marque2;
        int m_id;
        double m_x;
        double m_y;
        std::vector<const Sommet*> m_voisins; // tableau contenant les sommets voisins


    public : //m�thodes
        Sommet(int id, double x, double y);
        void ajouterVoisin(const Sommet*);
        int getId() const {return m_id;};
        int getX()const {return m_x;};
        int getY()const {return m_y;};
        int getMarque1(){return m_marque1;};        // Marque pour le poids 1
        int getMarque2(){return m_marque2;};        // Marque pour le poids 2
        void marquer1(){m_marque1=true;};
        void marquer2(){m_marque2=true;};
        void demarquer2(){m_marque2=false;};
        int verifierCC() const;
        std::vector<const Sommet*> getVoisins() const {return m_voisins;};
        void setVoisins() {m_voisins.clear();};
        ~Sommet();
        int get_x();
        int get_y();


};
#endif // SOMMET_H_INCLUDED



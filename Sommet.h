#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <queue>
#include <string>
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

    public : //méthodes
        Sommet(int id, double x, double y);
        int getId(){return m_id;};
        int getX(){return m_x;};
        int getY(){return m_y;};
        int getMarque1(){return m_marque1;};        // Marque pour le poids 1
        int getMarque2(){return m_marque2;};        // Marque pour le poids 2
        void marquer1(){m_marque1=true;};
        void marquer2(){m_marque2=true;};
        std::unordered_set<std::string> rechercherCC() const;
        std::string geterId() const {return m_id;};
        std::vector<const Sommet*> geterVoisins() const {return m_voisins;};
        ~Sommet();

};
#endif // SOMMET_H_INCLUDED


    private:
        /// Voisinage : liste d'adjacence
        std::vector<const Sommet*> m_voisins; // tableau contenant les sommets voisins

        /// Données spécifiques du sommet
        std::string m_id; // Identifiant / clé
        double m_x, m_y; // Position

};

#endif // SOMMET_H

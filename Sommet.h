#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

class Sommet
{

    private : //attributs
        bool m_marque; //sommet marqu� = ajout� dans l'arbre couvrant
        int m_id;
        double m_x;
        double m_y;

    public : //m�thodes
        Sommet(int id, double x, double y);
        int getId(){return m_id;};
        int getMarque(){return m_marque;};
        void marquer(){m_marque=true;};
        ~Sommet();

};
#endif // SOMMET_H_INCLUDED

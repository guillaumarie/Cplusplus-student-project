#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

class Sommet
{

    private : //attributs
        bool m_marque1; //sommet marqu� = ajout� dans l'arbre couvrant par rapport au poids 1
        bool m_marque2;
        int m_id;
        double m_x;
        double m_y;

    public : //m�thodes
        Sommet(int id, double x, double y);
        int getId(){return m_id;};
        int getX(){return m_x;};
        int getY(){return m_y;};
        int getMarque1(){return m_marque1;};        // Marque pour le poids 1
        int getMarque2(){return m_marque2;};        // Marque pour le poids 2
        void marquer1(){m_marque1=true;};
        void marquer2(){m_marque2=true;};
        ~Sommet();

};
#endif // SOMMET_H_INCLUDED

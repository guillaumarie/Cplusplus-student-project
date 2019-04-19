#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

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
        int getMarque1(){return m_marque1;};
        int getMarque2(){return m_marque2;};
        void marquer1(){m_marque1=true;};
        void marquer2(){m_marque2=true;};
        ~Sommet();
        int get_x();
        int get_y();


};
#endif // SOMMET_H_INCLUDED

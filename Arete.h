#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include <iostream>

class Arete
{
    private :
        int m_idArete;
        int m_id1;
        int m_id2;
        float m_poids1;
        float m_poids2;

    public :
        Arete(int idArete, int id1, int id2, float poids1, float poids2);
        int getId1(){return m_id1;};
        int getId2(){return m_id2;};
        int getPoids1(){return m_poids1;};
        int getPoids2(){return m_poids2;};
        void afficher();
        ~Arete();

};

#endif // ARETE_H_INCLUDED

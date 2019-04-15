#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include <iostream>

class Arete
{

    private :
        int m_poids;
        int m_id1;
        int m_id2;

    public :
        Arete(int id1,int id2,int poids);
        int getId1(){return m_id1;};
        int getId2(){return m_id2;};
        int getPoids(){return m_poids;};
        void afficher();
        ~Arete();

};

#endif // ARETE_H_INCLUDED

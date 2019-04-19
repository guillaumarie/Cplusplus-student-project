#include "Arete.h"

//constructeur
Arete::Arete(int idArete, int id1, int id2, float poids1, float poids2):m_idArete{idArete},m_id1{id1},m_id2{id2},m_poids1{poids1},m_poids2{poids2}
{
}

///------------------------------------------------------------------------

Arete::~Arete()
{}



float Arete::getPoids1()
{
    return m_poids1;
}
float Arete::getPoids2()
{
    return m_poids2;
}
int Arete::getId1()
{
    return m_id1;
}
int Arete::getId2()
{
    return m_id2;
}

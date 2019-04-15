#include "Arete.h"

//constructeur
Arete::Arete(int id1, int id2, int poids):m_id1{id1},m_id2{id2},m_poids{poids}
{
}


Arete::~Arete()
{}


void Arete::afficher()
{
    std::cout << "arete entre les sommets " << m_id2 << " et " << m_id1 << " de poids " << m_poids << std::endl;
}

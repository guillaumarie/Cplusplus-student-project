#include "Sommet.h"

//constructeur
Sommet::Sommet(int id, double x ,double y):m_marque1{false},m_marque2{false},m_id{id},m_x{x},m_y{y}
{
}

///------------------------------------------------------------------


Sommet::~Sommet()
{}

int Sommet::get_x()
{
    return m_x;
}
int Sommet::get_y()
{
    return m_y;
}

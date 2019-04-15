#include "Graphe.h"

/// CONSTRUCTEUR + RECUPERATION DONNEES FICHIER ____________________________

Graphe::Graphe(std::string nomFichierCoord, std::string nomFichierPoids)
{
    std::ifstream ifs{nomFichierCoord};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichierCoord );
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i)
    {
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet"); //lecture de l'indice/nom sommet
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.insert({id,new Sommet{id,x,y}});
    }

    //à ce moment la on arrive à la ligne qui indique le nombre d'arretes
    int taille;
    int id1;
    int id2;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_voisin;
    //lecture des aretes
    for (int i=0; i<taille; ++i)
    {
        //lecture des ids des deux extrémités
        ifs>>id1; // on récupère l'id 1 et 2
        ifs>>id2;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 1");
        //on crée une nouvelle variable de type arrete que l'on ajoute dans le conteneur de graphe
        m_aretes.push_back(new Arete{id1,id2});
    }
}


/// _________________________________________________________________
///ALGO DE PRIM

/** à un moment faire un test if arbre.m_sommets.size() == ordre du graphe de base -> alors c'est bien un arbre COUVRANT**/

void Graphe::algoPrim(int& indice)
{
    bool decouverts = true;
    int poids;

    m_sommets[indice-1]->marquer();

    do //tant que tous les sommets ne sont pas tous découverts
    {

        //parcourir toutes les arretes et garder celle qui a le plus petit poids parmis celles qui ont le sommet choisi comme extrémité
        Arete* best=nullptr;
        poids = 1000;
        for(auto j:m_arretes)
        {
            int s1 = j->getId1()-1; //indice du sommet
            int s2 = j->getId2()-1;

            if (   ( m_sommets[s1]->getMarque() && !m_sommets[s2]->getMarque())
                || ( m_sommets[s2]->getMarque() && !m_sommets[s1]->getMarque())  )
            {
                if (j->getPoids() < poids)
                {
                    poids = j->getPoids();
                    best = j;
                }
            }
        }
        // à ce niveau, best est l'arete de poids min
        int s1 = best->getId1()-1;
        int s2 = best->getId2()-1;

        if (  m_sommets[s1]->getMarque() && !m_sommets[s2]->getMarque() )
        {
            m_sommets[s2]->marquer();
        }
        if (  m_sommets[s2]->getMarque() && !m_sommets[s1]->getMarque() )
        {
            m_sommets[s1]->marquer();
        }

        m_aretesPrim.push_back(best);

        // --- vérif sortie boucle while
        decouverts = true;
        for(auto i:m_sommets) //on parcours tous les sommets
        {
            if(i->getMarque() == false)
                decouverts = false; //si on en trouve un qui n'est pas marqué on passe le découvert total à false
        }
        // --- fin vérif sortie boucle while

    }while(decouverts == false);

    // à ce niveau, les aretes de l'arbre de poids minimum
    for(auto a:m_aretesPrim)
        a->afficher();

}

/// _________________________________________________________________


Graphe::~Graphe()
{}


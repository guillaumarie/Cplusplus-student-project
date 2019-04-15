#include "Graphe.h"

/// CONSTRUCTEUR + RECUPERATION DONNEES FICHIER ____________________________

Graphe::Graphe(std::string nomFichierCoord, std::string nomFichierPoids)
{
    std::ifstream coord{nomFichierCoord};
    int ordre, taille1, taille2;
    if (!coord)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichierCoord );
    coord >> ordre;
    if ( coord.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

    int id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i)
    {
        coord>>id;
        if(coord.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet"); //lecture de l'indice/nom sommet
        coord>>x;
        if(coord.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet");
        coord>>y;
        if(coord.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet");
        m_sommets.push_back(new Sommet{id,x,y});
    }

    //� ce moment la on arrive � la ligne qui indique le nombre d'aretes
    int id1, id2, idArete;
    float poids1, poids2;
    coord >> taille1;
    if ( coord.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");

    std::ifstream weight{nomFichierPoids};      // On va �tudier le fichier poids
    if (!weight)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichierPoids );
    weight >> taille2;
    if ( weight.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");

    int nbrePoids;
    weight>>nbrePoids;
    if ( weight.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");

    //lecture des aretes
    if (taille1==taille2)
    {
        for (int i=0; i<taille2; ++i)
        {
            //lecture des ids des deux extr�mit�s
            coord>>idArete;
            if(coord.fail())
                throw std::runtime_error("Probleme lecture donn�es arete");
            coord>>id1; // on r�cup�re l'id 1 et 2
            if(coord.fail())
                throw std::runtime_error("Probleme lecture donn�es aretes");
            coord>>id2;
            if(coord.fail())
                throw std::runtime_error("Probleme lecture donn�es aretes");

            weight>>idArete;
            if(weight.fail())
                throw std::runtime_error("Probleme lecture donn�es arete1");
            weight>>poids1;
            if(weight.fail())
                throw std::runtime_error("Probleme lecture donn�es arete2");
            weight>>poids2;
            if(weight.fail())
                throw std::runtime_error("Probleme lecture donn�es arete3");
            //on cr�e une nouvelle variable de type arrete que l'on ajoute dans le conteneur de graphe
            m_aretes.push_back(new Arete{idArete,id1,id2,poids1,poids2});
        }
    }
    else
        std::cout<<"Le fichier poids ne correspond pas au fichier de coordonn�es de sommets"<<std::endl;
}


/// _________________________________________________________________
///ALGO DE PRIM

/** � un moment faire un test if arbre.m_sommets.size() == ordre du graphe de base -> alors c'est bien un arbre COUVRANT**/



void Graphe::algoPrim()
{
    bool decouverts = true;
    float poids1, poids2;

    m_sommets[0]->marquer1();
    m_sommets[0]->marquer2();

    do //tant que tous les sommets ne sont pas tous d�couverts
    {
        //parcourir toutes les aretes et garder celle qui a le plus petit poids parmis celles qui ont le sommet choisi comme extr�mit�
        Arete* meilleureArete=nullptr;
        poids1 = 10000.0;
        poids2 = 10000.0;

        for(auto j:m_aretes)        // Parcours graphe pour poids 1
        {
            int s1 = j->getId1(); //indice du sommet
            int s2 = j->getId2();

            if (   ( m_sommets[s1]->getMarque1() && !m_sommets[s2]->getMarque1())
                    || ( m_sommets[s2]->getMarque1() && !m_sommets[s1]->getMarque1())  )
            {
                if (j->getPoids1() < poids1)
                {
                    poids1 = j->getPoids1();
                    meilleureArete = j;
                }
            }
        }

        // � ce niveau, meilleureArete est l'arete de poids min
        int s1 = meilleureArete->getId1();
        int s2 = meilleureArete->getId2();

        if (  m_sommets[s1]->getMarque1() && !m_sommets[s2]->getMarque1() )
        {
            m_sommets[s2]->marquer1();
        }
        if (  m_sommets[s2]->getMarque1() && !m_sommets[s1]->getMarque1() )
        {
            m_sommets[s1]->marquer1();
        }

        m_aretesPrim1.push_back(meilleureArete);



        for(auto j:m_aretes)        // Parcours pour poids 2
        {
            int s1 = j->getId1(); //indice du sommet
            int s2 = j->getId2();

            if (   ( m_sommets[s1]->getMarque2() && !m_sommets[s2]->getMarque2())
                    || ( m_sommets[s2]->getMarque2() && !m_sommets[s1]->getMarque2())  )
            {
                if (j->getPoids2() < poids2)
                {
                    poids2 = j->getPoids2();
                    meilleureArete = j;
                }
            }
        }

        // � ce niveau, meilleureArete est l'arete de poids min
        s1 = meilleureArete->getId1();
        s2 = meilleureArete->getId2();

        if (  m_sommets[s1]->getMarque2() && !m_sommets[s2]->getMarque2() )
        {
            m_sommets[s2]->marquer2();
        }
        if (  m_sommets[s2]->getMarque2() && !m_sommets[s1]->getMarque2() )
        {
            m_sommets[s1]->marquer2();
        }

        m_aretesPrim2.push_back(meilleureArete);


        // --- v�rif sortie boucle while
        decouverts = true;
        for(auto i:m_sommets) //on parcours tous les sommets
        {
            if(i->getMarque1() == false || i->getMarque2() == false)
                decouverts = false; //si on en trouve un qui n'est pas marqu� on passe le d�couvert total � false
        }
        // --- fin v�rif sortie boucle while

    }
    while(decouverts == false);

    // � ce niveau, les aretes de l'arbre de poids minimum
    std::cout<<"Arbre couvrant de poids 1 minimum"<<std::endl<<std::endl;
    for(auto a:m_aretesPrim1)
        a->afficher1();
    std::cout<<std::endl<<std::endl<<"Arbre couvrant de poids 2 minimum"<<std::endl<<std::endl;
    for(auto b:m_aretesPrim2)
        b->afficher2();
}

/// _________________________________________________________________


Graphe::~Graphe()
{}


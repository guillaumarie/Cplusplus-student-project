#include "Graphe.h"
#include <math.h>
#include <unordered_map>


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
    int id1,x1,y1,id2,x2,y2;
    float poids1, poids2;

    m_sommets[0]->marquer1();
    m_sommets[0]->marquer2();

    do //tant que tous les sommets ne sont pas tous d�couverts
    {
        //parcourir toutes les aretes et garder celle qui a le plus petit poids parmis celles qui ont le sommet choisi comme extr�mit�
        Arete* meilleureArete=nullptr;
        poids1 = 10000.0;
        poids2 = 10000.0;


        /// Parcours pour poids 2

        for(auto j:m_aretes)
        {
            id1 = j->getId1(); //indice du sommet
            id2 = j->getId2();

            if (   ( m_sommets[id1]->getMarque1() && !m_sommets[id2]->getMarque1())
                    || ( m_sommets[id2]->getMarque1() && !m_sommets[id1]->getMarque1())  )
            {
                if (j->getPoids1() < poids1)
                {
                    poids1 = j->getPoids1();
                    meilleureArete = j;
                }
            }
        }

        // � ce niveau, meilleureArete est l'arete de poids min
        id1 = meilleureArete->getId1();
        id2 = meilleureArete->getId2();

        if (  m_sommets[id1]->getMarque1() && !m_sommets[id2]->getMarque1() )
        {
            m_sommets[id2]->marquer1();
        }
        if (  m_sommets[id2]->getMarque1() && !m_sommets[id1]->getMarque1() )
        {
            m_sommets[id1]->marquer1();
        }

        x1 = m_sommets[id1]->getX();
        y1 = m_sommets[id1]->getY();
        x2 = m_sommets[id2]->getX();
        y2 = m_sommets[id2]->getY();

        m_aretesPrim1.push_back(id1,x1,y1,id2,x2,y2,poids1,poids2);



        /// Parcours pour poids 2

        for(auto j:m_aretes)
        {
            id1 = j->getId1(); //indice du sommet
            id2 = j->getId2();

            if (   ( m_sommets[id1]->getMarque2() && !m_sommets[id2]->getMarque2())
                    || ( m_sommets[id2]->getMarque2() && !m_sommets[id1]->getMarque2())  )
            {
                if (j->getPoids2() < poids2)
                {
                    poids2 = j->getPoids2();
                    meilleureArete = j;
                }
            }
        }

        // � ce niveau, meilleureArete est l'arete de poids min
        id1 = meilleureArete->getId1();
        id2 = meilleureArete->getId2();

        if (  m_sommets[id1]->getMarque2() && !m_sommets[id2]->getMarque2() )
        {
            m_sommets[id2]->marquer2();
        }
        if (  m_sommets[id2]->getMarque2() && !m_sommets[id1]->getMarque2() )
        {
            m_sommets[id1]->marquer2();
        }

        x1 = m_sommets[id1]->getX();
        y1 = m_sommets[id1]->getY();
        x2 = m_sommets[id2]->getX();
        y2 = m_sommets[id2]->getY();

        m_aretesPrim2.push_back(id1,x1,y1,id2,x2,y2,poids1,poids2);


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
    int poids1Tot=0, poids2Tot=0;
    for(auto a:m_aretesPrim1)
    {
        poids1=a->getPoids1();
        poids2=a->getPoids2();
        poids1Tot=poids1Tot+poids1;
        poids2Tot=poids2Tot+poids2;
    }

    poids1Tot=0;
    poids2Tot=0;
    for(auto b:m_aretesPrim2)
    {
        poids1=b->getPoids1();
        poids2=b->getPoids2();
        poids1Tot=poids1Tot+poids1;
        poids2Tot=poids2Tot+poids2;
    }
}

/// _________________________________________________________________

void Graphe::algoPareto()
{
    int nombre = m_aretes.size();
    int numeroPossibilite=0;
    int exposant=0,reste=0;
    std::vector<int> nombreBinaire;
    std::unordered_map<int,std::vector<int>> possibilites;
    for(int i=0; i<nombre; ++i )
    {
        numeroPossibilite=i;
        // On commence par cr�er une liste en binaire, chaque indice correspondant � une ar�te
        exposant=0,reste=0;
        while (pow(2,exposant) < numeroPossibilite)      // Tant que la puissance de 2 ne peut pas contenir le nombre bits
            ++exposant;
        do
        {
            reste=numeroPossibilite%2;             // On calcule son reste dans la division euclidienne par 2
            nombreBinaire.push_back(reste);
            nombre = numeroPossibilite/2;
        }while(numeroPossibilite >= 2);               // Tant que le nombre est sup�rieur � 2

        nombreBinaire.push_back(numeroPossibilite);
        possibilites.insert({i,nombreBinaire});
    }
    for(size_t k=0; k<possibilites.size(); ++k)
    {
        auto search = possibilites.find(k);
        if (search != possibilites.end())

            std::cout<<"Found "<<search->first<<" "<<std::endl;
        else
            std::cout<<"Not found"<<std::endl;
    }
}

/// _________________________________________________________________

Graphe::~Graphe()
{}


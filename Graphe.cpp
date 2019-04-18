#include "Graphe.h"
#include <math.h>


/// CONSTRUCTEUR + RECUPERATION DONNEES FICHIER ____________________________

Graphe::Graphe(std::string nomFichierCoord, std::string nomFichierPoids)
{
    std::ifstream coord{nomFichierCoord};
    int taille1, taille2;
    if (!coord)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichierCoord );
    coord >> m_ordre;
    if ( coord.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

    int id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<m_ordre; ++i)
    {
        coord>>id;
        if(coord.fail())
            throw std::runtime_error("Probleme lecture données sommet"); //lecture de l'indice/nom sommet
        coord>>x;
        if(coord.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        coord>>y;
        if(coord.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.push_back(new Sommet{id,x,y});
    }

    //à ce moment la on arrive à la ligne qui indique le nombre d'aretes
    int id1, id2, idArete;
    float poids1, poids2;
    coord >> taille1;
    if ( coord.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");

    std::ifstream weight{nomFichierPoids};      // On va étudier le fichier poids
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
            //lecture des ids des deux extrémités
            coord>>idArete;
            if(coord.fail())
                throw std::runtime_error("Probleme lecture données arete");
            coord>>id1; // on récupère l'id 1 et 2
            if(coord.fail())
                throw std::runtime_error("Probleme lecture données aretes");
            coord>>id2;
            if(coord.fail())
                throw std::runtime_error("Probleme lecture données aretes");

            weight>>idArete;
            if(weight.fail())
                throw std::runtime_error("Probleme lecture données arete1");
            weight>>poids1;
            if(weight.fail())
                throw std::runtime_error("Probleme lecture données arete2");
            weight>>poids2;
            if(weight.fail())
                throw std::runtime_error("Probleme lecture données arete3");
            //on crée une nouvelle variable de type arrete que l'on ajoute dans le conteneur de graphe
            m_aretes.push_back(new Arete{idArete,id1,id2,poids1,poids2});
        }
    }
    else
        std::cout<<"Le fichier poids ne correspond pas au fichier de coordonnées de sommets"<<std::endl;
}


/// _________________________________________________________________
///ALGO DE PRIM

/** à un moment faire un test if arbre.m_sommets.size() == ordre du graphe de base -> alors c'est bien un arbre COUVRANT**/



void Graphe::algoPrim()
{
    bool decouverts = true;
    int id1,id2;
    float poids1, poids2;

    m_sommets[0]->marquer1();
    m_sommets[0]->marquer2();

    do //tant que tous les sommets ne sont pas tous découverts
    {
        //parcourir toutes les aretes et garder celle qui a le plus petit poids parmis celles qui ont le sommet choisi comme extrémité
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

        // à ce niveau, meilleureArete est l'arete de poids min
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

        m_aretesPrim1.push_back(meilleureArete);



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

        // à ce niveau, meilleureArete est l'arete de poids min
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

        m_aretesPrim2.push_back(meilleureArete);


        // --- vérif sortie boucle while
        decouverts = true;
        for(auto i:m_sommets) //on parcours tous les sommets
        {
            if(i->getMarque1() == false || i->getMarque2() == false)
                decouverts = false; //si on en trouve un qui n'est pas marqué on passe le découvert total à false
        }
        // --- fin vérif sortie boucle while

    }
    while(decouverts == false);

    // à ce niveau, les aretes de l'arbre de poids minimum
    m_poids1Tot1=0;
    m_poids2Tot1=0;
    m_poids1Tot2=0;
    m_poids2Tot2=0;
    for(auto a:m_aretesPrim1)
    {
        poids1=a->getPoids1();
        poids2=a->getPoids2();
        m_poids1Tot1=m_poids1Tot1+poids1;
        m_poids2Tot1=m_poids2Tot1+poids2;
    }

    for(auto b:m_aretesPrim2)
    {
        poids1=b->getPoids1();
        poids2=b->getPoids2();
        m_poids1Tot2=m_poids1Tot2+poids1;
        m_poids2Tot2=m_poids2Tot2+poids2;
    }
}

/// _________________________________________________________________

void Graphe::algoPareto()
{
    int numeroPossibilite=0, reste=0, nombreAretes=0, compte=0, id1, id2, cc, nombre=pow(2,m_aretes.size());
    float idGraphe=0, poids1, poids2, poids1Tot, poids2Tot, poids1TotMin, poids2TotMin;
    std::vector<int> nombreBinaire;
    std::vector<float> grapheSelectionnes;        // Vecteur d'arêtes sélectionnées pour une solution
    std::vector<int> idSelectionnes;
    std::vector<std::vector<float>> espaceRecherche;
    int cmpt=0;

    for(int i=0; i<nombre; ++i )        // Parcours des possibilités
    {
        numeroPossibilite=i;                // Solution possible traitée en ce moment
        compte=0, cc=0;

        /// Conversion de numeroPossibilte en binaire
        // On commence par créer une liste en binaire, chaque indice correspondant à une arête
        do
        {
            reste=numeroPossibilite%2;             // On calcule son reste dans la division euclidienne par 2
            nombreBinaire.push_back(reste);         // On ajoute le reste (0 ou 1) au vecteur nombreBinaire
            numeroPossibilite = numeroPossibilite/2;           // Et on garde le quotient de la division
        }
        while(numeroPossibilite >= 2);                // Tant que le nombre est supérieur à 2
        nombreBinaire.push_back(numeroPossibilite);     // On ajoute le dernier quotient (0 ou 1) au vecteur nombreBinaire

        /// Calcul du nombre d'arêtes
        nombreAretes = 0;
        for(auto n:nombreBinaire)        // Parcours des 0 et 1 du vecteur nombreBinaire (pour étudier les arêtes sélectionnées)
        {
            if(n == 1)        // Si l'élément est égal à 1
                ++nombreAretes;            // On incrémente le nombre de 1 dans le nombre binaire (donc le nombre d'arêtes sélectionnées)
        }


        /// Si nombreAretes = m_ordre-1, on récupère les identifiants des arêtes sélectionnées
        /// Puis on répertorie tous les voisins
        /// Puis on s'assure que tous les sommets sont bien dans la même composante connexe
        /// Si oui, on ajoute toutes les arêtes de la possibilité étudiée à un vecteur d'arêtes
        if(nombreAretes == m_ordre-1)         // Si le nombre d'arêtes d'une solution potentielle est égal à l'ordre-1
        {
            for(auto n:nombreBinaire)        // Parcours de tous les éléments (0 ou 1) du nombre binaire
            {
                if(n == 1)      // Si l'élément du nombre binaire est égal à 1
                {
                    idSelectionnes.push_back(compte);
                    id1 = m_aretes[compte]->getId1();
                    id2 = m_aretes[compte]->getId2();
                    m_sommets[id1]->ajouterVoisin(m_sommets[id2]);          // On ajoute le sommet id2 aux voisins de id1
                    m_sommets[id2]->ajouterVoisin(m_sommets[id1]);          // On ajoute le sommet id2 aux voisins de id1
                }
                ++compte;
            }
            cc = m_sommets[id1]->verifierCC();        // Recherche des composantes connexes à partir du sommet id1 (n'importe quel sommet)

            for(auto id:idSelectionnes)         // Réinitialisation des voisins pour chaque sommet dont on les a répertoriés dans la partie précédente
            {
                id1 = m_aretes[id]->getId1();
                id2 = m_aretes[id]->getId2();
                m_sommets[id1]->setVoisins();
                m_sommets[id2]->setVoisins();
            }

            poids1Tot=0;                 // Réinitialisation des poids 1 et 2 totaux
            poids2Tot=0;
            if(cc == m_ordre)      // Si tous les sommest sont dans la composante connexe au départ de n'importe quel sommet (ici : id1)
            {
                grapheSelectionnes.push_back(idGraphe);        // Le numéro du graphe entre dans le vecteur graphe (le premier est 1)
                for(auto id:idSelectionnes)       // On parcourt tous les idSelectionnés
                {
                    poids1 = m_aretes[id]->getPoids1();       // Poids 1 de l'arête
                    poids2 = m_aretes[id]->getPoids2();       // Poids 2 de l'arête
                    poids1Tot = poids1Tot + poids1;       // On additionne le poids 1 au poids 1 total
                    poids2Tot = poids2Tot + poids2;       // On additionne le poids 2 au poids 2 total
                }
                grapheSelectionnes.push_back(poids1Tot);     // On entre le poidsTotal 1
                grapheSelectionnes.push_back(poids2Tot);     // On entre le poidsTotal 2
                ++cmpt;

                espaceRecherche.push_back(grapheSelectionnes);      // On ajoute chaque graphe (vecteur) solution au vecteur espace de recherche

                /*
                std::cout<<"Solution "<<i<<std::endl;
                for(int j=0; j<m_ordre-1; ++j)
                {
                    int id=idSelectionnes[j];
                    std::cout<<id<<" ";
                }
                std::cout<<std::endl;
                */

            }
            idSelectionnes.clear();                 // On vide le vecteur idSelectionnes
            grapheSelectionnes.clear();             // On vide le vecteur grapheSelectionnes
        }
        nombreBinaire.clear();                  // On vide le nombre binaire de ses éléments
        ++idGraphe;
    }
    std::cout<<cmpt<<std::endl;

    /*
    std::vector<float> grapheTraite;
    /// Tri des graphes de l'espace de recherche selon leurs poids
    for(auto e:espaceRecherche)
    {
        grapheTraite=e;
        if(grapheTraite[1])
    }
    */
}

/// _________________________________________________________________





Graphe::~Graphe()
{}


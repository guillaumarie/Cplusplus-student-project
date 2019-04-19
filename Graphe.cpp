#include "Graphe.h"
#include "menu.h"
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

std::vector<Arete*> Graphe::getm_Arete()
{
    return m_aretes;
}






/// _________________________________________________________________

bool comp(const std::pair<float,float> &a, const std::pair<float,float> &b)     // Comparateur utilisé pour trié les poids à la fin de l'algorithme
{
    return a.second < b.second;
}

void Graphe::algoPareto()
{
    int numeroPossibilite=0, reste=0, nombreAretes=0, compte=0, id1, id2, cc, nombre=pow(2,m_aretes.size());
    float idGraphe=0, poids1, poids2, poids1Tot, poids2Tot, xMin, yActuel;
    std::vector<int> nombreBinaire;
    std::vector<int> idSelectionnes;
    std::vector<std::pair<float,float>> triPoids1;
    std::vector<std::pair<float,float>> triPoids2Temp;
    std::vector<std::pair<float,float>> triPoids2;
    std::vector<float> pointPareto;
    std::vector<float> pointNuage;
    std::vector<std::vector<float>> frontierePareto;
    std::vector<std::vector<float>> nuagePoints;
    //int cmpt=0;


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
                for(auto id:idSelectionnes)       // On parcourt tous les idSelectionnés
                {
                    poids1 = m_aretes[id]->getPoids1();       // Poids 1 de l'arête
                    poids2 = m_aretes[id]->getPoids2();       // Poids 2 de l'arête
                    poids1Tot = poids1Tot + poids1;       // On additionne le poids 1 au poids 1 total
                    poids2Tot = poids2Tot + poids2;       // On additionne le poids 2 au poids 2 total
                }
                //++cmpt;

                std::pair <float,float> pair1 = std::make_pair (idGraphe, poids1Tot);
                std::pair <float,float> pair2 = std::make_pair (idGraphe, poids2Tot);
                triPoids1.push_back(pair1);
                triPoids2Temp.push_back(pair2);
            }
            idSelectionnes.clear();                 // On vide le vecteur idSelectionnes
        }
        nombreBinaire.clear();                  // On vide le nombre binaire de ses éléments
        ++idGraphe;
    }
    //std::cout<<cmpt<<std::endl;


    std::sort(triPoids1.begin(), triPoids1.end(), comp);        // Tri des poids1 par ordre croissant

    int rang=0;
    for(auto t1:triPoids1)
    {
        for(auto t2:triPoids2Temp)
        {
            if(t2.first==t1.first)
            {
                triPoids2.push_back(t2);
                break;
            }
        }
    }

    xMin = triPoids1[0].second;     // xMin est la valeur minimale des poids1
    yActuel = triPoids2[0].second;     // yActuel est la valeur du poids2 correspondant au poid1 min

    rang=0;
    for(auto t1:triPoids1)
    {
        if(t1.second != xMin)
        {
            if(triPoids2[rang].second < yActuel)
            {
                yActuel = triPoids2[rang].second;
                xMin = t1.second;
                pointPareto.push_back(t1.first);
                pointPareto.push_back(t1.second);
                pointPareto.push_back(yActuel);
                frontierePareto.push_back(pointPareto);
                pointPareto.clear();
            }
            else
            {
                pointNuage.push_back(t1.first);
                pointNuage.push_back(t1.second);
                pointNuage.push_back(triPoids2[rang].second);
                nuagePoints.push_back(pointNuage);
                pointNuage.clear();
            }
        }
        else if(t1.second == xMin)
        {
            if(triPoids2[rang].second < yActuel)
            {
                while(frontierePareto.back()[1]==xMin)
                {
                    nuagePoints.push_back(frontierePareto.back());
                    frontierePareto.pop_back();
                }
                yActuel = triPoids2[rang].second;
                pointPareto.push_back(t1.first);
                pointPareto.push_back(t1.second);
                pointPareto.push_back(yActuel);
                frontierePareto.push_back(pointPareto);
                pointPareto.clear();
            }
            else if(triPoids2[rang].second == yActuel)
            {
                pointPareto.push_back(t1.first);
                pointPareto.push_back(t1.second);
                pointPareto.push_back(yActuel);
                frontierePareto.push_back(pointPareto);
                pointPareto.clear();
            }
            else
            {
                pointNuage.push_back(t1.first);
                pointNuage.push_back(t1.second);
                pointNuage.push_back(triPoids2[rang].second);
                nuagePoints.push_back(pointNuage);
                pointNuage.clear();
            }
        }
        ++rang;
    }

    /*
    std::cout<<"Frontiere Pareto"<<std::endl;
    for(int i=0; i<frontierePareto.size(); ++i)
    {
        std::cout<<"idGraphe : "<<frontierePareto[i][0]<<"  poidsTot1 : "<<frontierePareto[i][1]<<"  poidstot2 : "<<frontierePareto[i][2]<<std::endl;
    }
    */

    /*
        std::cout<<std::endl<<"Nuage"<<std::endl;
        for(int i=0; i<nuagePoints.size(); ++i)
        {
            std::cout<<"idGraphe : "<<nuagePoints[i][0]<<"  poidsTot1 : "<<nuagePoints[i][1]<<"  poidstot2 : "<<nuagePoints[i][2]<<std::endl;
        }
    */
}

/// _________________________________________________________________

Graphe::~Graphe()
{}

/// _________________________________________________________________

void Graphe::dessinerGraphe() //Dessiner les graphes
{
    BITMAP* monbuffer = create_bitmap(1400,750);
    std::vector<Sommet*> vecteur_de_sommets;
    for(const auto& itA : m_aretes)     // parcours de m_aretes
    {
        int id_1;
        id_1=  itA->getId1();
        int id_2;
        id_2=  itA->getId2();

        for(const auto& itt : m_sommets) // parcours de m_sommets
        {
            int sommetId = itt->getId();
            if (sommetId ==id_1)
                vecteur_de_sommets.push_back(itt);

            if  (sommetId==id_2)
                vecteur_de_sommets.push_back(itt);
        }
        int coord_x1 = vecteur_de_sommets[0]->getX(); // pour dessiner les aretes on recuperes les coordonees des 2 sommets
        int coord_y1 = vecteur_de_sommets[0]->getY();
        int coord_x2 = vecteur_de_sommets[1]->getX();
        int coord_y2 = vecteur_de_sommets[1]->getY();
        line(monbuffer, coord_x1, coord_y1, coord_x2, coord_y2, makecol(0,255,255));
        vecteur_de_sommets.clear();
        for(const auto& it : m_sommets) // parcours de m_sommets
        {
            circlefill(monbuffer, it->getX(), it->getY(),8,makecol(220,181,255)); // on dessine tous les sommets
            textprintf_ex(monbuffer,font,it->getX()+12,it->getY()-12,makecol(130,255,167),-1,"%d",it->getId()); // on indique les indices d'aretes

        }
        blit(monbuffer,screen,0,0,0,0,1400,750);

    }
}
void Graphe::dessinerPrim1() // pour dessinerl'arbre couvrant de poids 1 minimum
{
    //float poids2Tot = 0;
    //float poids1Tot =0;
    BITMAP* monbuffer = create_bitmap(1400,750);
    std::vector<Sommet*> vecteur_de_sommets;

    for(const auto& itA : m_aretesPrim1)
    {
        std::cout <<"test";
        int id_1;
        id_1=  itA->getId1();
        int id_2;
        id_2=  itA->getId2();
        //poids1Tot = poids1Tot+itA->getPoids1();
        //poids2Tot = poids2Tot+itA->getPoids2();

        for(const auto& itt : m_sommets)
        {
            int sommetId = itt->getId();
            if (sommetId ==id_1)
                vecteur_de_sommets.push_back(itt);

            if  (sommetId==id_2)
                vecteur_de_sommets.push_back(itt);
        }
        int coord_x1 = vecteur_de_sommets[0]->getX();
        int coord_y1 = vecteur_de_sommets[0]->getY();
        int coord_x2 = vecteur_de_sommets[1]->getX();
        int coord_y2 = vecteur_de_sommets[1]->getY();
        line(monbuffer, coord_x1, coord_y1, coord_x2, coord_y2, makecol(0,255,255));
        vecteur_de_sommets.clear();
        for(const auto& it : m_sommets)
        {
            circlefill(monbuffer, it->getX(), it->getY(),8,makecol(220,181,255));
            textprintf_ex(monbuffer,font,it->getX()+12,it->getY()-12,makecol(130,255,167),-1,"%d",it->getId());
        }
        if(itA==m_aretesPrim2.back())
            textprintf_centre_ex(monbuffer,font,200,690,makecol(236,202,232),-1, "le poids total est ( %2.2f ; %2.2f  )", m_poids1Tot1, m_poids2Tot1);
        blit(monbuffer,screen,0,0,0,0,1400,750);
    }
}
void Graphe::dessinerPrim2() // pour dessinerl'arbre couvrant de poids 1 minimum
{
    //float poids2Tot = 0;
    //float poids1Tot =0;
    BITMAP* monbuffer = create_bitmap(1400,750);
    std::vector<Sommet*> vecteur_de_sommets;
    for(const auto& itA : m_aretesPrim2)
    {
        int id_1;
        id_1=  itA->getId1();
        int id_2;
        id_2=  itA->getId2();
        //poids1Tot = poids1Tot+itA->getPoids1();
        //poids2Tot = poids2Tot+itA->getPoids2();

        for(const auto& itt : m_sommets)
        {
            int sommetId = itt->getId();
            if (sommetId ==id_1)
                vecteur_de_sommets.push_back(itt);

            if  (sommetId==id_2)
                vecteur_de_sommets.push_back(itt);
        }
        int coord_x1 = vecteur_de_sommets[0]->getX();
        int coord_y1 = vecteur_de_sommets[0]->getY();
        int coord_x2 = vecteur_de_sommets[1]->getX();
        int coord_y2 = vecteur_de_sommets[1]->getY();
        line(monbuffer, coord_x1, coord_y1, coord_x2, coord_y2, makecol(254,120,251));
        vecteur_de_sommets.clear();

        for(const auto& it : m_sommets)
        {
            circlefill(monbuffer, it->getX(), it->getY(),8,makecol(255,255,183));
            textprintf_ex(monbuffer,font,it->getX()+12,it->getY()-12,makecol(236,202,232),-1,"%d",it->getId());
        }
        if(itA==m_aretesPrim2.back())
            textprintf_centre_ex(monbuffer,font,200,690,makecol(236,202,232),-1, "le poids total est ( %2.2f ; %2.2f )", m_poids1Tot2, m_poids2Tot2);
        blit(monbuffer,screen,0,0,0,0,1400,750);
    }

}
///std::vector<std::vector<float>> frontiere,std::vector<std::vector<float>> combiPareto
void Graphe::dessinerPareto()
{
    BITMAP* monbuffer1 = create_bitmap(1400,750);
    rectfill(monbuffer1, 0, 0, 1400,750, makecol(255,255,255));
    circlefill(monbuffer1,20,730,1,makecol(140,0,255));
    rectfill(monbuffer1, 20, 730, 1340,734, makecol(140,0,255)); // Utilisation de rectfill pour pouvoir faire des axes épais
    rectfill(monbuffer1, 20, 730,24,30, makecol(140,0,255));
    textprintf_ex(monbuffer1,font,1340+6,730+6,makecol(0,85,255),-1,"cout 1");
    textprintf_ex(monbuffer1,font,20-6,30-12,makecol(0,85,255),-1,"cout 2");
    blit(monbuffer1,screen,0,0,0,0,1400,750);
    ///for(auto coor : frontiere)
    // {
    //circlefill(monbuffer1,20+coor[0],695-coor[1],makecol(0,255,0));
// }
}


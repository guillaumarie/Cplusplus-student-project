#include "Graphe.h"
#include "menu.h"

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
    float poids1, poids2;

    m_sommets[0]->marquer1();
    m_sommets[0]->marquer2();

    do //tant que tous les sommets ne sont pas tous découverts
    {
        //parcourir toutes les aretes et garder celle qui a le plus petit poids parmis celles qui ont le sommet choisi comme extrémité
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

        // à ce niveau, meilleureArete est l'arete de poids min
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

        // à ce niveau, meilleureArete est l'arete de poids min
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


 Graphe::~Graphe()
{}

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
        int coord_x1 = vecteur_de_sommets[0]->get_x(); // pour dessiner les aretes on recuperes les coordonees des 2 sommets
        int coord_y1 = vecteur_de_sommets[0]->get_y();
        int coord_x2 = vecteur_de_sommets[1]->get_x();
        int coord_y2 = vecteur_de_sommets[1]->get_y();
        line(monbuffer, coord_x1, coord_y1, coord_x2, coord_y2, makecol(0,255,255));
        vecteur_de_sommets.clear();
    for(const auto& it : m_sommets) // parcours de m_sommets
    {
        circlefill(monbuffer, it->get_x(), it->get_y(),8,makecol(220,181,255)); // on dessine tous les sommets
        textprintf_ex(monbuffer,font,it->get_x()+12,it->get_y()-12,makecol(130,255,167),-1,"%d",it->getId()); // on indique les indices d'aretes

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
        int coord_x1 = vecteur_de_sommets[0]->get_x();
        int coord_y1 = vecteur_de_sommets[0]->get_y();
        int coord_x2 = vecteur_de_sommets[1]->get_x();
        int coord_y2 = vecteur_de_sommets[1]->get_y();
        line(monbuffer, coord_x1, coord_y1, coord_x2, coord_y2, makecol(151,255,117));
        vecteur_de_sommets.clear();
    for(const auto& it : m_sommets)
    {
        circlefill(monbuffer, it->get_x(), it->get_y(),8,makecol(220,181,255));
        textprintf_ex(monbuffer,font,it->get_x()+12,it->get_y()-12,makecol(130,255,167),-1,"%d",it->getId());
    }
     if(itA==m_aretesPrim2.back())
            textprintf_centre_ex(monbuffer,font,200,690,makecol(236,202,232) ,-1, "le poids total est ( %2.2f ; %2.2f  )", m_poids1Tot1, m_poids2Tot1);
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
        int coord_x1 = vecteur_de_sommets[0]->get_x();
        int coord_y1 = vecteur_de_sommets[0]->get_y();
        int coord_x2 = vecteur_de_sommets[1]->get_x();
        int coord_y2 = vecteur_de_sommets[1]->get_y();
        line(monbuffer, coord_x1, coord_y1, coord_x2, coord_y2, makecol(254,120,251));
        vecteur_de_sommets.clear();

        for(const auto& it : m_sommets)
        {
            circlefill(monbuffer, it->get_x(), it->get_y(),8,makecol(255,255,183));
            textprintf_ex(monbuffer,font,it->get_x()+12,it->get_y()-12,makecol(236,202,232),-1,"%d",it->getId());
        }
        if(itA==m_aretesPrim2.back())
            textprintf_centre_ex(monbuffer,font,200,690,makecol(236,202,232) ,-1, "le poids total est ( %2.2f ; %2.2f )", m_poids1Tot2, m_poids2Tot2);
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


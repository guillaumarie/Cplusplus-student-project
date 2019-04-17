#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include <vector>
#include <math.h>
#include <fstream>
#include <string>
#include <allegro.h>

/*int affichage_menu ()
{
    install_mouse();
    show_mouse(screen);
    BITMAP* buffer_menu = create_bitmap(1200,800);
    BITMAP* imagedefond=load_bitmap()
}*/
void allegro()
{
    BITMAP*page;
    // On va utiliser du hasard
    srand(time(NULL));

    // Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1200,750,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // CREATION DU BUFFER D'AFFICHAGE à la taille de l'écran
    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);
}


int main()
{

    int choix=0;
    Graphe graphe("triville.txt", "triville_weights_0.txt");
    graphe.algoPrim();

allegro();

    std::cout << "Que voulez vous afficher ?"<<std::endl;
    std::cout<<"1-Afficher le graphe"<<std::endl;
    std::cout<<"2-Affcher le premier arbre couvrantde poids minimum"<<std::endl;
    std::cout<<"3-Afficher le deuxieme arbre couvant de poids minimum "<<std::endl;
    std::cin >> choix;

    switch(choix)
    {
        case 1 :
           graphe.dessinerGraphe();
            break;

        case 2 :
            graphe.dessinerPrim1();
            break;

        case 3 :
            graphe.dessinerPrim2();
            break;

    }


   while(!key[KEY_ESC])
   {

   }
    return 0;
}
END_OF_MAIN();

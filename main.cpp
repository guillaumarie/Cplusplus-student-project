#include <iostream>
#include <ctime>
#include <chrono>
#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include <vector>
#include <math.h>
#include <fstream>
#include <string>
#include <allegro.h>
#include "menu.h"


void allegro()
{
    BITMAP*page;
    // On va utiliser du hasard
    srand(time(NULL));

    // Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1400,750,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // CREATION DU BUFFER D'AFFICHAGE à la taille de l'écran
    page=create_bitmap(1400,750);
    clear_bitmap(page);
}


int main()
{
    std::clock_t c_start = std::clock();                // Début horloge temps cpu
    auto t_start = std::chrono::high_resolution_clock::now();       // Début horloge temps réel


    Graphe graphe("triville.txt", "triville_weights_0.txt");
    graphe.algoPrim();
    graphe.algoPareto();
    graphe.algoDijkstra();
    allegro();

    /*
        std::cout << "Que voulez vous afficher ?"<<std::endl;
        std::cout<<"1-Afficher le graphe"<<std::endl;
        std::cout<<"2-Affcher le premier arbre couvrantde poids minimum"<<std::endl;
        std::cout<<"3-Afficher le deuxieme arbre couvant de poids minimum "<<std::endl;
        std::cout<<"4-Afficher le graphe de Pareto "<<std::endl;
        std::cin >> choix;
    */

    std::clock_t c_end = std::clock();              // Fin horloge temps cpu
    auto t_end = std::chrono::high_resolution_clock::now();     // Fin horloge temps réel
    std::cout << "Total time taken by CPU: " << 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC << " ms" << std::endl;
    std::cout << "Total real time: " << std::chrono::duration<double, std::milli>(t_end-t_start).count() << " ms" << std::endl;


    while(!key[KEY_ESC])
        affichage_menu(graphe);


    return 0;
}
END_OF_MAIN();

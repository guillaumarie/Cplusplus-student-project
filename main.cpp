#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include <vector>
#include <math.h>
#include <fstream>
#include <string>
#include <allegro.h>

void allegro()
{
    BITMAP*page;
    // On va utiliser du hasard
    srand(time(NULL));

    // Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
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
    Graphe graphe("manhattan.txt", "manhattan_weights_0.txt");
    graphe.algoPrim();

allegro();
 graphe.placerSommets();
   while(!key[KEY_ESC])
   {

   }
    return 0;
}
END_OF_MAIN();

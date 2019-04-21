#include "menu.h"
#include <allegro.h>
#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include <vector>
#include <math.h>
#include <fstream>
#include <string>


void affichage_menu (Graphe graphe) // fonction pour afficher le menu
{
    install_mouse(); //initialisation souris
    show_mouse(screen); //affichage souris
    BITMAP* buffer_menu = create_bitmap(1400,750);
    BITMAP *menu_all_options= load_bitmap("fond.bmp",NULL); //ouverture menu
    BITMAP *bouton1= load_bitmap("clique1.bmp",NULL);
    BITMAP *bouton2= load_bitmap("clique2.bmp",NULL);
    BITMAP *bouton3= load_bitmap("clique3.bmp",NULL);
    BITMAP *bouton4= load_bitmap("clique4.bmp",NULL);
    BITMAP *bouton5= load_bitmap("clique5.bmp",NULL);
    //blit(menu_all_options,buffer_menu,0,0,0,0,1400,75);
    //blit(buffer_menu,screen,0,0,0,0,1400,750);
    int choix=0;

    while (!key[KEY_ESC]) //pour quitter, appuyer sur la touche echap
        {
            blit(menu_all_options,buffer_menu,0,0,0,0,1400,750);

           if (mouse_x>68 && mouse_x<312 )  // devenir blanc quand on approche de la case 1 et choix=1 si clic
            {
                if( mouse_y>82 && mouse_y<107)
                {
                   blit(bouton1,buffer_menu,0,0,0,0,1400,750);
                    if (mouse_b & 1)
                    {
                        choix = 1;
                        break;
                    }
                }
            }

                if (mouse_x>96 && mouse_x<284) // devenir blanc quand on approche de la case 2 et choix=2 si clic
            {
                if (mouse_y>209 && mouse_y<266)
                {
                    blit(bouton2,buffer_menu,0,0,0,0,1400,750);
                    if (mouse_b & 1)
                    {
                        choix = 2;
                        break;
                    }
                }
             }

             if (mouse_x>95 && mouse_x<285) // devenir clair quand on approche de la case 3 et choix=3 si clic
            {
                if (mouse_y>348 && mouse_y<397)
                {
                    blit(bouton3,buffer_menu,0,0,0,0,1400,750);
                    if (mouse_b & 1)
                    {
                        choix = 3;
                        break;
                    }
                }
            }

            if (mouse_x>53 && mouse_x<329) // devenir blanc quand on approche de la case 4 et choix=4 si clic
            {
                if (mouse_y>468 && mouse_y<526)
                {
                    blit(bouton4,buffer_menu,0,0,0,0,1400,750);
                    if (mouse_b & 1)
                    {
                        choix = 4;
                        break;
                    }
                }
            }

            if (mouse_x>52 && mouse_x<330) // devenir blanc quand on approche de la case 5 et choix=5 si clic
            {
                if (mouse_y>614 && mouse_y<663)
                {
                    blit(bouton5,buffer_menu,0,0,0,0,1400,750);
                    if (mouse_b & 1)
                    {
                        choix = 5;
                        break;
                    }
                }
            }

        blit(buffer_menu, screen,0,0,0,0,1400,750);
        clear_bitmap(buffer_menu);

        }
 switch(choix)
    {
        case 1 :
                graphe.dessinerGraphe();

                while (!key[KEY_SPACE]){}  // pour retourner au menu appuyer sur la barre d'espace
                rest(100);
            break;

        case 2 :
           graphe.dessinerPrim1();
            while (!key[KEY_SPACE]){} // pour retourner au menu appuyer sur la barre d'espace
                rest(100);
            break;

        case 3 :
            graphe.dessinerPrim2();
            while (!key[KEY_SPACE]){} // pour retourner au menu appuyer sur la barre d'espace
                rest(100);
            break;
      case 4 :

           graphe.algoPareto();
           graphe.dessinerPareto(graphe.getFrontier(),graphe.getNuage());
           while (!key[KEY_SPACE]){} // pour retourner au menu appuyer sur la barre d'espace
                rest(100);
           break;

    }
}

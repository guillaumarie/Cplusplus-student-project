#include "menu.h"
#include <allegro.h>
#include <iostream>
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
    BITMAP *fondmenu = load_bitmap("image_de_fond.bmp",NULL); //ouerture image fond
    BITMAP *menu_all_options= load_bitmap("MENU_de_base.bmp",NULL); //ouverture menu
    BITMAP *bouton1= load_bitmap("clique1.bmp",NULL);
    BITMAP *bouton2= load_bitmap("clique2.bmp",NULL);
    BITMAP *bouton3= load_bitmap("clique3.bmp",NULL);
    BITMAP *bouton4= load_bitmap("clique4.bmp",NULL);
    BITMAP *bouton5= load_bitmap("clique5.bmp",NULL);
    BITMAP *bouton6= load_bitmap("clique6.bmp",NULL);
    BITMAP *bouton7= load_bitmap("clique7.bmp",NULL);
    draw_sprite(buffer_menu,fondmenu,0,0);
    draw_sprite(buffer_menu,menu_all_options,0,0);
    blit(buffer_menu,screen,0,0,0,0,1400,750);
 int choix = 0;

    while (!key[KEY_ESC]) //pour quitter, appuyer sur la touche echap
        {
            blit(fondmenu,buffer_menu,0,0,0,0,1400,750);
            draw_sprite(buffer_menu,menu_all_options,0,0);

            if (mouse_x>85 && mouse_x<348)  // devenir blanc quand on approche de la case 1 et choix=1 si clic
            {
                if (mouse_y>65 && mouse_y<145)
                {
                    draw_sprite(buffer_menu,bouton1,0,0);
                    if (mouse_b & 1)
                    {
                        choix = 1;
                        break;
                    }
                }
            }

                if (mouse_x>419 && mouse_x<680) // devenir blanc quand on approche de la case 2 et choix=2 si clic
            {
                if (mouse_y>72 && mouse_y<145)
                {
                    draw_sprite(buffer_menu,bouton2,0,0);
                    if (mouse_b & 1)
                    {
                        choix = 2;
                        break;
                    }
                }
             }

             if (mouse_x>751 && mouse_x<1012) // devenir blanc quand on approche de la case 3 et choix=3 si clic
            {
                if (mouse_y>68 && mouse_y<146)
                {
                    draw_sprite(buffer_menu,bouton3,0,0);
                    if (mouse_b & 1)
                    {
                        choix = 3;
                        break;
                    }
                }
            }

            if (mouse_x>1082 && mouse_x<1343) // devenir blanc quand on approche de la case 4 et choix=4 si clic
            {
                if (mouse_y>65 && mouse_y<144)
                {
                    draw_sprite(buffer_menu,bouton4,0,0);
                    if (mouse_b & 1)
                    {
                        choix = 4;
                        break;
                    }
                }
            }

            if (mouse_x>259 && mouse_x<520) // devenir blanc quand on approche de la case 5 et choix=5 si clic
            {
                if (mouse_y>170 && mouse_y<249)
                {
                    draw_sprite(buffer_menu,bouton5,0,0);
                    if (mouse_b & 1)
                    {
                        choix = 5;
                        break;
                    }
                }
            }
            if (mouse_x>590 && mouse_x<851) // devenir blanc quand on approche de la case 6 et choix=6 si clic
            {
                if (mouse_y>170 && mouse_y<249)
                {
                    draw_sprite(buffer_menu,bouton6,0,0);
                    if (mouse_b & 1)
                    {
                        choix = 6;
                        break;
                    }
                }
            }
            if (mouse_x>933 && mouse_x<1194) // devenir blanc quand on approche de la case 7 et choix=7 si clic
            {
                if (mouse_y>169 && mouse_y<248)
                {
                    draw_sprite(buffer_menu,bouton7,0,0);
                    if (mouse_b & 1)
                    {
                        choix = 7;
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
           graphe.dessinerPareto();
           while (!key[KEY_SPACE]){} // pour retourner au menu appuyer sur la barre d'espace
                rest(100);
           break;

    }
}

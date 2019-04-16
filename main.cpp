#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include <vector>

int main()
{
    Graphe graphe("broadway.txt", "broadway_weights_0.txt");
    graphe.algoPrim();
    graphe.algoPareto();


    return 0;
}

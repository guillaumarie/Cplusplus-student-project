#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include <vector>

void algoPrim(Sommet* sommetDepart);

int main()
{
    Graphe graphe("broadway.txt", "broadway_weights_0.txt");
    graphe.algoPrim();


    return 0;
}

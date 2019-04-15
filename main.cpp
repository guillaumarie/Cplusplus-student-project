#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include <vector>

void algoPrim(Sommet* sommetDepart);

int main()
{
    Graphe graphe("manhattan.txt", "manhattan_weights_0.txt");
    graphe.algoPrim(indice);
// jezn frncis

    return 0;
}

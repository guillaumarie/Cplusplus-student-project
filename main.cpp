#include <iostream>
#include <ctime>
#include <chrono>
#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include <vector>

int main()
{
    std::clock_t c_start = std::clock();                // Début horloge temps cpu
    auto t_start = std::chrono::high_resolution_clock::now();       // Début horloge temps réel


    Graphe graphe("manhattan.txt", "manhattan_weights_0.txt");
    graphe.algoPrim();
    graphe.algoPareto();



    std::clock_t c_end = std::clock();              // Fin horloge temps cpu
    auto t_end = std::chrono::high_resolution_clock::now();     // Fin horloge temps réel
    std::cout << "Total time taken by CPU: " << 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC << " ms" << std::endl;
    std::cout << "Total real time: " << std::chrono::duration<double, std::milli>(t_end-t_start).count() << " ms" << std::endl;

    return 0;
}

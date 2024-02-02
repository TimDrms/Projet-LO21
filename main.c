#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "population.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));                            // Initialise la génération de nombres aléatoires
    int taillePop = rand() % (200 - 20 + 1) + 20; // Nombre d'individus entre 20 et 200
    int nbGen = rand() % (200 - 20 + 1) + 20;     // Nombre de générations entre 20 et 200
    int nbCrois = 2;                              // Nombre de croisements par génération

    // Création de la population
    Population *pop;

    // Répétition du processus nbGen fois
    for (int i = 0; i < nbGen; i++)
    {
        // Initialisation de la population
        pop = creerPopulation(taillePop);

        // Affichage de la population
        printf("Population numero %d :\n", i);
        afficherPopulation(pop);

        // Croisement de la population
        printf("Population croisee :\n");
        pop = croiserPopulation(pop, nbCrois, taillePop);
        afficherPopulation(pop);

        // Tri de la population
        printf("Population triee :\n");
        triPopulation(pop);

        // Sélection
        printf("Population selectionnee :\n");
        Population *popSelect = selection(pop, 4, taillePop);
        afficherPopulation(popSelect);

        // Afficher le meilleur individu
        printf("Meilleur individu :\n");
        afficherMeilleurIndividu(popSelect);
        printf("\n\n");
    }

    return 0;
}
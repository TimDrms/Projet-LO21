#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "individu.h"

typedef struct Population
{
    Individu *ind;
    struct Population *next;
} Population;


Population *creerPopulation(int nbIndiv);
void afficherPopulation(Population *pop);
void quicksort(int *tab, int nbIndiv);
void triPopulation(Population *pop);
Population *selection(Population *pop, int tSelect, int nbIndiv);
Population *croiserPopulation(Population *pop, int nbCrois, int nbIndiv);
void afficherMeilleurIndividu(Population *pop);
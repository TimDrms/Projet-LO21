#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "population.h"


/*!
* @brief Création d'une population de nbIndiv individus
* @param nbIndiv Nombre d'individus dans la population
* @return Pointeur vers la population
*/
Population *creerPopulation(int nbIndiv)
{
    Population *pop = (Population *)malloc(sizeof(Population));
    pop->ind = creerIndividu();
    pop->next = NULL;
    Population *tmp = pop;
    for (int i = 1; i < nbIndiv; i++)
    {
        tmp->next = (Population *)malloc(sizeof(Population));
        tmp = tmp->next;
        tmp->ind = creerIndividu();
        tmp->next = NULL;
    }
    return pop;
}

/*!
* @brief Fonction qui affiche tous les individus d'une population
* @param pop Population à analyser
*/
void afficherPopulation(Population *pop)
{
    Population *tmp = pop;
    int i = 0;
    while (tmp != NULL)
    {
        printf("Individu numero %d : ", i);
        for (int j = 0; j < longueurIndiv; j++)
        {
            printf("%d", tmp->ind->bit[j]);
        }
        printf(" | Valeur decodee : %d", decodeur(tmp->ind));
        printf(" | Qualite : %d\n", calculQualite_f1(tmp->ind));
        tmp = tmp->next;
        i++;
    }
    printf("\n");
}

/*!
* @brief Fonction qui trie un tableau à l'aide d'un quicksort
* @param tab Tableau à trier
* @param nbIndiv Nombre d'individus dans la population
*/
void quicksort(int *tab, int nbIndiv)
{
    int i = 0;
    int j = nbIndiv - 1;
    int pivot = tab[nbIndiv / 2];
    while (i <= j)
    {
        while (tab[i] < pivot)
        {
            i++;
        }
        while (tab[j] > pivot)
        {
            j--;
        }
        if (i <= j)
        {
            int tmp = tab[i];
            tab[i] = tab[j];
            tab[j] = tmp;
            i++;
            j--;
        }
    }
    if (j > 0)
    {
        quicksort(tab, j + 1);
    }
    if (i < nbIndiv)
    {
        quicksort(tab + i, nbIndiv - i);
    }
}

/*!
* @brief Fonction qui tri une population par ordre décroissant de qualité des individus grâce à la fonction quicksort
* @param pop Pointeur vers la population à trier
*/
void triPopulation(Population *pop)
{
    int nbIndiv = 0;
    Population *tmp = pop;
    while (tmp != NULL)
    {
        nbIndiv++;
        tmp = tmp->next;
    }
    int *qualite = malloc(nbIndiv * sizeof(int));
    tmp = pop;
    for (int i = 0; i < nbIndiv; i++)
    {
        qualite[i] = calculQualite_f1(tmp->ind);
        tmp = tmp->next;
    }
    quicksort(qualite, nbIndiv);

    int j = 0; // Indice de l'individu
    for (int i = nbIndiv - 1; i >= 0; i--)
    {
        printf("Individu numero %d | Qualite : %d\n", j, qualite[i]);
        j++;
    }
    printf("\n");
}

/*!
* @brief Fonction qui sélectionne les individus d'une population ayant une qualité supérieure à un seuil donné défini par tSelect
* @param pop Pointeur vers la population à analyser
* @param tSelect Seuil de sélection
* @param nbIndiv Nombre d'individus dans la population
* @return Pointeur vers la nouvelle population
*/
Population *selection(Population *pop, int tSelect, int nbIndiv)
{
    Population *tmp = pop;
    Population *newPop = (Population *)malloc(sizeof(Population));
    Population *tmp2 = newPop;
    int compteur = 0;

    // On parcourt la population et on ajoute les individus qui ont une qualité supérieure à tSelect
    for (int i = 0; i < nbIndiv - 1; i++)
    {
        if (calculQualite_f1(tmp->ind) >= tSelect)
        {
            tmp2->ind = tmp->ind;
            tmp2->next = (Population *)malloc(sizeof(Population));
            tmp2 = tmp2->next;
            compteur++;
        }
        tmp = tmp->next;
    }

    // On complète la population par recopie des tSelect premiers éléments
    Population *tmp3 = newPop;
    while (compteur < nbIndiv - 1)
    {
        tmp2->ind = tmp3->ind;
        tmp2->next = (Population *)malloc(sizeof(Population));
        tmp2 = tmp2->next;
        tmp3 = tmp3->next;
        compteur++;
    }
    tmp2->ind = tmp3->ind;
    tmp2->next = NULL;
    return newPop;
}

/*!
* @brief Fonction qui croise une population, c'est à dire à partir d’une Population P1, créer une seconde Population P2, constituée d’Individus sélectionnés aléatoirement deux à deux dans P1 et croisés entre eux
* @param pop Pointeur vers la population à croiser
* @param nbCrois Nombre d'individus à croiser
* @param nbIndiv Nombre d'individus dans la population
* @return Pointeur vers la nouvelle population
*/
Population *croiserPopulation(Population *pop, int nbCrois, int nbIndiv)
{
    Population *newPop = (Population *)malloc(sizeof(Population));
    Population *tmp = newPop;
    for (int i = 0; i < nbCrois; i++)
    {
        tmp->ind = croiserIndividu(pop->ind, pop->next->ind);
        tmp->next = (Population *)malloc(sizeof(Population));
        tmp = tmp->next;
        pop = pop->next;
    }
    // On complète la population avec les individus restants pour avoir nbIndiv individus
    for (int i = 0; i < nbIndiv - nbCrois - 1; i++)
    {
        tmp->ind = pop->ind;
        tmp->next = (Population *)malloc(sizeof(Population));
        tmp = tmp->next;
        pop = pop->next;
    }
    tmp->ind = pop->ind;
    tmp->next = NULL;
    return newPop;
}

/*!
* @brief Fonction qui affiche l'individu ayant la meilleure valeur la plus haute d'une population
* @param pop Pointeur vers la population à analyser
*/
void afficherMeilleurIndividu(Population *pop)
{
    Population *tmp = pop;
    int valeurMax = 0;
    int valeur = 0;
    Individu *ind = (Individu *)malloc(sizeof(Individu));
    while (tmp != NULL)
    {
        valeur = decodeur(tmp->ind);
        if (valeur > valeurMax)
        {
            valeurMax = valeur;
            ind = tmp->ind;
        }
        tmp = tmp->next;
    }
    afficherIndividu(ind);
}
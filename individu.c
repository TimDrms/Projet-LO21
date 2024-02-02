#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "individu.h"



/*                              /!\ ATTENTION /!\
Pour utiliser la fonction calculQualite_f2 il faut remplacer la valeur de longueurIndiv par 16
et remplacer dans les fonctions qui l'utilisent, la fonction "calculQualite_f1" par "calculQualite_f2"
ainsi que remplacer le tSelect utilisé lors de l'appel à la fonction selection dans le main
*/



/*!
* @brief Fonction qui crée un individu aléatoire
* @return un pointeur vers l'individu créé
*/
Individu *creerIndividu()
{
    Individu *ind = (Individu *)malloc(sizeof(Individu));
    ind->bit = malloc(longueurIndiv * sizeof(Bit));
    ind->longIndiv = longueurIndiv;
    for (int i = 0; i < longueurIndiv; i++)
    {
        ind->bit[i] = rand() % 2;
    }
    return ind;
}

/*!
* @brief Fonction qui crée un individu aléatoire de manière récursive
* @param i un entier qui sert de compteur qui commence à 0
* @return un pointeur vers l'individu créé
*/
Individu *creerIndividuRec(int i)
{
    Individu *ind = (Individu *)malloc(sizeof(Individu));
    ind->bit = malloc(longueurIndiv * sizeof(Bit));
    ind->longIndiv = longueurIndiv;
    if (i < longueurIndiv)
    {
        ind->bit[i] = rand() % 2;
        ind = creerIndividuRec(i + 1);
    }
    return ind;
}

/*!
* @brief Fonction qui décode la valeur d'un individu
* @param ind un pointeur vers l'individu que l'on va décoder
* @return la valeur décoder de l'individu
*/
int decodeur(Individu *ind)
{
    int x = 0;
    for (int i = 0; i < longueurIndiv; i++)
    {
        x += ind->bit[i] * pow(2, longueurIndiv - i - 1);
    }
    return x;
}

/*!
* @brief Fonction qui calcule la qualité d'un individu pour la fonction f1
* @param ind un pointeur vers l'individu dont on va calculer la qualité
* @return la qualité de l'individu
*/
int calculQualite_f1(Individu *ind)
{
    int x = decodeur(ind);
    int A = -1;
    int B = 1;
    x = pow(-(x / pow(2, longueurIndiv)) * (B - A) + A, 2);
    return x;
}

/*!
* @brief Fonction qui calcule la qualité d'un individu pour la fonction f2
* @param ind un pointeur vers l'individu dont on va calculer la qualité
* @return la qualité de l'individu
*/
int calculQualite_f2(Individu *ind)
{
    int x = decodeur(ind);
    int A = 0.1;
    int B = 5;
    x = -log((x / pow(2, longueurIndiv)) * (B - A) + A);
    return x;
}

/*!
* @brief Fonction qui affiche un individu
* @param ind un pointeur vers l'individu que l'on va afficher
*/
void afficherIndividu(Individu *ind)
{
    for (int i = 0; i < longueurIndiv; i++)
    {
        printf("%d", ind->bit[i]);
    }
    printf(" | Valeur decodee : %d", decodeur(ind));
    printf(" | Qualite : %d\n", calculQualite_f1(ind));
}

/*!
* @brief Fonction qui croise deux listes de bits, c'est à dire intervertir les éléments des deux listes selo  une probabilité donnée (pCroise) pour chaque position dans la liste (tirage aléatoire et comparaison avec la probabilité)
* @param ind1 un pointeur vers l'individu 1
* @param ind2 un pointeur vers l'individu 2
* @return un pointeur vers l'individu créé qui est croisé
*/
Individu *croiserIndividu(Individu *ind1, Individu *ind2)
{
    Individu *newInd = (Individu *)malloc(sizeof(Individu));
    newInd = creerIndividu();
    int pCroise = 50;
    for (int i = 0; i < longueurIndiv; i++)
    {
        int alea = rand() % 100;
        if (alea < pCroise)
        {
            newInd->bit[i] = ind1->bit[i];
        }
        else
        {
            newInd->bit[i] = ind2->bit[i];
        }
    }
    return newInd;
}
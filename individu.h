#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define longueurIndiv 8 // longueur d'un individu

typedef unsigned char Bit; // Définition du type Bit

typedef struct individu
{
    Bit *bit;      // 0 ou 1
    int longIndiv; // longueur de l'individu
} Individu;

typedef struct elem
{
    Individu *ind;     // pointeur vers un individu
    struct elem *next; // pointeur vers l'élément suivant
} element;

typedef element *list; // pointeur vers un élément

Individu *creerIndividu();
int decodeur(Individu *ind);
int calculQualite_f1(Individu *ind);
int calculQualite_f2(Individu *ind);
void afficherIndividu(Individu *ind);
Individu *croiserIndividu(Individu *ind1, Individu *ind2);
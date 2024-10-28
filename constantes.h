#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#define MAX_PLAYERS 14
#define SIZE_ROLE 13
#define SIZE_NAME 20
#define SIZE_STATE 7
#define NUMBER_OF_ROUNDS 4

// Def Structures

typedef struct Player Player;
struct Player
{
    char Role[SIZE_ROLE]; /* On met tout en statique car plus rapide*/ 
    char Name[SIZE_NAME];
    char State[SIZE_STATE]; /*Nous permet d'y enregistrer si se couche et si suit ou raise*/
    int Money;
    int Bet;
    int dead;/* 0 if alive*/
    int isAllin; 
    /* Add First to play beacause the one raising should be the first to play next round*/
};
//




#endif
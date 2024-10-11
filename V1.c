#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_PLAYERS 14
#define SIZE_ROLE 11
#define SIZE_NAME 20
#define SIZE_STATE 7
// Def Structures

typedef struct Player Player;
struct Player
{
    char Role[SIZE_ROLE]; /* On met tout en statique car plus rapide*/ 
    char Name[SIZE_NAME];
    char State[SIZE_STATE]; /*Nous permet d'y enregistrer si ALL IN, si se couche et si suit ou raise ou Mort*/
    int Money;
    int Bet;
    /* Add First to play beacause the one raising should be the first to play next round*/
};
//

void PrintPokerBanner() {
    printf("\n\n");
    printf("PPPP    OOO   K   K  EEEEE  RRRR  \n");
    printf("P   P  O   O  K  K   E      R   R \n");
    printf("PPPP   O   O  KKK    EEEE   RRRR  \n");
    printf("P      O   O  K  K   E      R R   \n");
    printf("P       OOO   K   K  EEEEE  R  RR \n");
    printf("\n\n");
}

void Display_Of_Players(Player *Array_Of_Players, int Index) /*Takes a record of player and the index of our player */
{
    printf("Money :%d, Name:%s",((&Array_Of_Players[Index])->Money), (&Array_Of_Players[Index])->Name);
}

void Initialization_Of_A_Player(char *Name, int Money, char *Role_g, char *State_g, Player *Player_Yet_To_Initialise) /*Here we would give the adresse of let's say Array_Of_Players[0] in order to only affect this one*/
{
    /**/
    strcpy(Player_Yet_To_Initialise->Name, Name);/*Nous permet de copier Name dans Player_Yet_To_Initialise*/

    strcpy(Player_Yet_To_Initialise->Role, Role_g);

    strcpy(Player_Yet_To_Initialise->State, State_g);

    /* Modifications attributs */
    Player_Yet_To_Initialise->Money = Money;
    Player_Yet_To_Initialise->Bet = 0;
}

void Definition_Of_All_Players(Player *Array_Of_Player, int Players_In_Game)
{
    char Name[SIZE_NAME];
    char Role[SIZE_ROLE] = "Neutre";
    char State[SIZE_STATE] ="Neutre";
    int Money = 2000;
    while (Players_In_Game < 5) 
    {
        printf("Please, enter the name of player %d : ", Players_In_Game);
        if (fgets(Name,SIZE_NAME,stdin) !=NULL && *Name!='.') 
        {
            Initialization_Of_A_Player(Name, Money, Role,State, &Array_Of_Player[Players_In_Game]);
            Display_Of_Players(Array_Of_Player,Players_In_Game);
            Players_In_Game++;
        } 
        else 
        { 
            printf("\n Error get or end of acquisition \n",stderr);
            break;
        } 

    }    

}


void Initialisation_Roles(Player *Array_Of_Players)
{
    /* On initialise les rôles de manière assez bête , 0 prend Dealer, 1 Prend SB, 2 BB*/
    strcpy((&Array_Of_Players[0])->Role,"Dealer");
    strcpy((&Array_Of_Players[1])->Role,"Small Blind");
    strcpy((&Array_Of_Players[2])->Role,"Big Blind"); /* Do tests To make sure of performances*/
}


void Ajouter_Argent(Player *Player_Selected, int *Money_Incremented)
{
    Player_Selected->Money += *Money_Incremented;
}

void Afficher_Options()
{
    printf("\nPossible Actions :\n");
    printf("1. Raise\n");
    printf("2. Call\n");
    printf("3. Fold\n");
    printf("4. All-In\n");
    printf("Choisissez votre action (1, 2, 3, 4) : ");
}
    

int main()
{
    PrintPokerBanner();
    int Number_Od_Player =0; /* Initialisation */
    Player Array_Of_Players[MAX_PLAYERS];
    Definition_Of_All_Players(Array_Of_Players, Number_Od_Player);
    
    /*------------------------------------------*/
    Display_Of_Players(Array_Of_Players,1);
    Initialisation_Roles(Array_Of_Players);



    /*-----------------------------------------*/

    return 0;
}

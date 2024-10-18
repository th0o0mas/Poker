#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_PLAYERS 14
#define SIZE_ROLE 13
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
    int dead; /* 0 if alive*/
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
    printf("\nMoney :%d Name:%s Role : %s",((&Array_Of_Players[Index])->Money), (&Array_Of_Players[Index])->Name, (&Array_Of_Players[Index])->Role);
    printf("Role : %s \n", (&Array_Of_Players[Index])->Role);
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
    int Players_Incremental = 0;
    char Name[SIZE_NAME];
    char Role[SIZE_ROLE] = "Neutre";
    char State[SIZE_STATE] ="Neutre";
    int Money = 2000;
    while (Players_Incremental < Players_In_Game) 
    {
        printf("Please, enter the name of player %d : ", Players_Incremental+1);
        if (fgets(Name,SIZE_NAME,stdin) !=NULL && *Name!='.') 
        {
            Initialization_Of_A_Player(Name, Money, Role,State, &Array_Of_Player[Players_Incremental]);
            Players_Incremental++;
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


void Add_Money(Player *Player_Selected, int Money_Incremented)
{
    Player_Selected->Money += Money_Incremented;
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

void Betting_Add_On_Modifying_Money(Player *Player_selected, int Bet)
{
    Add_Money(Player_selected, -Bet);
}

void Verify_Players_Have_Money(Player *Array_Of_Players, int Number_of_Players)
{
    for (int i=0; i<Number_of_Players; i++)
    {
        if ((Array_Of_Players[i].Money)==0)
        {
            printf(" \n %s is dead \n", Array_Of_Players[i].Name);
            Array_Of_Players[i].dead = 1;
        }
    }
}



void Whole_Betting(Player *Array_Of_Players, int Number_Of_Players, int Small_Blind)
{
    /*  Small Blind laways bet first (could implement the guy raising being the first one to bid) */
    int Index_SB,Index_BB;
    int Option;
    int Bet;
    Verify_Players_Have_Money(Array_Of_Players, Number_Of_Players);
    for (int i=0; i<Number_Of_Players;i++)
    {    
        if (strcmp(Array_Of_Players[i].Role,"Small Blind"))
        {
            Index_SB =i;
        }
        if (strcmp(Array_Of_Players[i].Role,"Big Blind"))
        {
            Index_BB =i;
        }
    }

    printf("Small Blind is $%d", Small_Blind);
    /* We make the Small Blind pay*/
    if (Array_Of_Players[Index_SB].Money > Small_Blind )
    {
        // No worries we just bet as usual
        Betting_Add_On_Modifying_Money(&(Array_Of_Players[Index_SB]),Small_Blind);
    }
    else if (Array_Of_Players[Index_SB].dead) /* Means he's all in*/
    {

    }

    


}
    

int main()
{
    PrintPokerBanner();

    int Number_Of_Players =0; /* Initialisation */
    printf("\n \n How many players are present : ");
    scanf("%d", &Number_Of_Players);
    getchar();
    Player Array_Of_Players[Number_Of_Players];
    Definition_Of_All_Players(Array_Of_Players, Number_Of_Players);
    
    /*------------------------------------------*/
    Initialisation_Roles(Array_Of_Players);
    for (int i=0; i<Number_Of_Players;i++)
    {    
        Display_Of_Players(Array_Of_Players,i);
    }
    


    /*-----------------------------------------*/

    return 0;
}

#include "initialisations.h"
#include "constantes.h"

void clearTerminal() {
#ifdef _WIN32
    system("cls");  // commande fixe pour Windows
#else
    system("clear");  // commande fixe pour Linux/macOS
#endif
}
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
    if (strcmp(Array_Of_Players[Index].State,"Fold")!=0)
    {    printf("\n %s's balance is %d and is Role is %s , Bet = %d  \n",(&Array_Of_Players[Index])->Name,((&Array_Of_Players[Index])->Money), (&Array_Of_Players[Index])->Role,(&Array_Of_Players[Index])->Bet);
    }
    else
    {
        printf("\n  %s %s's %s balance is %d and is Role is %s , Bet = %d  \n",KRED,(&Array_Of_Players[Index])->Name,KNRM,((&Array_Of_Players[Index])->Money), (&Array_Of_Players[Index])->Role,(&Array_Of_Players[Index])->Bet);
    }
}


void Initialization_Of_A_Player(char *Name, int Money, char *Role_g, char *State_g, Player *Player_Yet_To_Initialise) /*Here we would give the adresse of let's say Array_Of_Players[0] in order to only affect this one*/
{
    /**/
    strcpy(Player_Yet_To_Initialise->Name, Name);/*Nous permet de copier Name dans Player_Yet_To_Initialise*/

    strcpy(Player_Yet_To_Initialise->Role, Role_g);

    strcpy(Player_Yet_To_Initialise->State, State_g);

    /* Modifications attributs */
    Player_Yet_To_Initialise->Money = Money;
    Player_Yet_To_Initialise->isAllin = 0;
    Player_Yet_To_Initialise->Bet = 0;
}

void Definition_Of_All_Players(Player *Array_Of_Player, int Players_In_Game)
{
    int Players_Incremental = 0;
    char Name[SIZE_NAME];
    char Role[SIZE_ROLE] = "Neutre";
    char State[SIZE_STATE] ="N";
    int Money = 2000;
    while (Players_Incremental < Players_In_Game) 
    {
        printf("Please, enter the name of player %d : ", Players_Incremental+1);
        if (fgets(Name,SIZE_NAME,stdin) !=NULL) 
        {
            Name[strcspn(Name, "\n")] = '\0';
            Initialization_Of_A_Player(Name, Money, Role,State, &Array_Of_Player[Players_Incremental]);
            Players_Incremental++;
        } 
        else 
        { 
            fputs("\n Error get or end of acquisition \n",stderr);
            break;
        } 

    }    

}


void Initialisation_Roles(Player *Array_Of_Players, int Number_Of_Players)
{
    /* On initialise les rôles de manière assez bête , 0 prend Dealer, 1 Prend SB, 2 BB*/
    strcpy((&Array_Of_Players[0])->Role,"Dealer");
    strcpy((&Array_Of_Players[1])->Role,"Small Blind");
    if (Number_Of_Players>2)
        strcpy((&Array_Of_Players[2])->Role,"Big Blind"); /* Do tests To make sure of performances*/
}



void break_round(int *SB){
    int choice;
    printf("What do you want to do now?\nChoose between the followings propositions :\n1. Continue\n2. Change Blinds\nChoose your action (1, 2, 3, 4) : ");
    scanf("%d",&choice);
    while (choice!=1 && choice!=2){
        printf("Please enter a correct value\nChoose your action (1, 2, 3, 4) : ");
        scanf("%d",&choice);
    }
    switch (choice){
        case 1: return;
        case 2: printf("Enter the new small blind value :");
        scanf("%d",SB);
    }
}

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
    int dead;/* 0 if alive*/
    int isAllin; 
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
            fputs("\n Error get or end of acquisition \n",stderr);
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

Player * Verify_Players_Have_Money(Player *Array_Of_Players, int *Number_of_Players)
{
    int New_number_of_players = *Number_of_Players;
    for (int i=0; i<*Number_of_Players; i++) /* First loop only to figure out how many players are remaining*/
    {
        if ((Array_Of_Players[i].Money)==0)
        {
            printf(" %s is dead ", Array_Of_Players[i].Name);
            Array_Of_Players[i].dead = 1;
            New_number_of_players--;
        }
    }
   
    Player *New_Array=malloc(sizeof(*New_Array));
    int Incrementable = 0;
    
    for (int i=0; i<*Number_of_Players;i++)
    {
       if ((Array_Of_Players[i].Money)!=0)
        {
            
            New_Array[i-Incrementable]=Array_Of_Players[i]; /* Incrementable is here to make sure that wa fill New_Array in the logical order of indexes ( 0,1,...)*/
        }
        else
        {
            printf("\n On a un mort \n");
            Incrementable++;
        }
    }
    
    *Number_of_Players = New_number_of_players;
    return New_Array;
}

void Switch_Roles(Player *Array_Of_PLayer, int Number_Of_Player)
{
    int Index_Dealer,Index_SB,Index_BB;
    for (int i=0; i<Number_Of_Player; i++)
    {
        if (strcmp(Array_Of_PLayer[i].Role,"Dealer")==0)
        {
            Index_Dealer = i;
        }
        else if (strcmp(Array_Of_PLayer[i].Role,"Small Blind")==0)
        {
            Index_SB = i;
        }
        else if (strcmp(Array_Of_PLayer[i].Role,"Big Blind")==0)
        {
            Index_BB = i;
        }
    }
    if (Index_Dealer<Number_Of_Player-1) /*Means we don't have to start the array at 0*/
    {
        strcpy(Array_Of_PLayer[Index_Dealer].Role,"Neutre");/* It's the only one that needs to be put to Neutral in case of more than 3 player*/
        strcpy(Array_Of_PLayer[Index_Dealer+1].Role,"Dealer");
    }

    else /* Means Index_Dealer is the last element of our array*/
    {
        strcpy(Array_Of_PLayer[0].Role,"Dealer");
    }

    if (Index_SB<Number_Of_Player-1) /*Means we don't have to start the array at 0*/
    {
        strcpy(Array_Of_PLayer[Index_SB+1].Role,"Small BLind");
    }
    else /* Means Index_SB is the last element of our array*/
    {
        strcpy(Array_Of_PLayer[0].Role,"Small BLind");
    }

    if (Index_BB<Number_Of_Player-1) /*Means we don't have to start the array at 0*/
    {
        strcpy(Array_Of_PLayer[Index_BB+1].Role,"Big Blind");
    }
    else /* Means Index_BB is the last element of our array*/
    {
        strcpy(Array_Of_PLayer[0].Role,"Big Blind");
    }



}


void Did_Bet(Player *Array_Of_Players, int Index_the_one_betting, int Bet)
{
    Array_Of_Players[Index_the_one_betting].Bet = Bet;
}

void Whole_Betting(Player *Array_Of_Players, int Number_Of_Players, int Small_Blind)
{
    /*  Small Blind laways bet first (could implement the guy raising being the first one to bid) */
    int Index_SB,Index_BB,Index_Dealer,Bet;
    Verify_Players_Have_Money(Array_Of_Players, &Number_Of_Players);
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
        if (strcmp(Array_Of_Players[i].Role,"Dealer"))
        {
            Index_Dealer =i;
        }
    }
    printf("/n -------------------- /n");
    printf("\n Small Blind is $%d \n", Small_Blind);
    printf("/n -------------------- /n");
    
    /* We make the Small Blind pay*/
    if (Array_Of_Players[Index_SB].Money > Small_Blind )
    {
        // No worries we just bet as usual
        Bet = Small_Blind;
        Betting_Add_On_Modifying_Money(&(Array_Of_Players[Index_SB]),-Bet);
    }
    else  /*Means he's all in beacause verifying players have money would have deleted the mad before this function*/
    {
        Bet = Array_Of_Players[Index_SB].Money;
        Did_Bet(Array_Of_Players,Index_SB,Bet);
        Array_Of_Players[Index_SB].isAllin=1;
        Betting_Add_On_Modifying_Money(&(Array_Of_Players[Index_SB]), -Array_Of_Players[Index_SB].Money);
    }
    /*Small Blind is done betting for now*/

    /* We make big blind pay now*/
    if (Array_Of_Players[Index_SB].isAllin==0)
    {
        if (Array_Of_Players[Index_SB].Money > (Bet<<2))
        {
            Bet = Bet<<2;
            Did_Bet(Array_Of_Players,Index_BB,Bet);
            Betting_Add_On_Modifying_Money(&(Array_Of_Players[Index_BB]), -Bet);
        }
        else
        {
            Bet = Array_Of_Players[Index_BB].Money;
            Did_Bet(Array_Of_Players,Index_BB,Bet);
            Array_Of_Players[Index_BB].isAllin=1;
            Betting_Add_On_Modifying_Money(&(Array_Of_Players[Index_BB]), -Array_Of_Players[Index_BB].Money);
        }
    }
    else
    {
        /* The bet does not change*/
        if (Array_Of_Players[Index_BB].Money > Bet)
        {
            Did_Bet(Array_Of_Players,Index_BB,Bet);
            Betting_Add_On_Modifying_Money(&(Array_Of_Players[Index_BB]), -Bet);
        }
        else /* Covers cases if BB has as musch money as the SB or less*/
        {
            
             int Bet2 = Array_Of_Players[Index_BB].Money; /* Changes nothing if whole money equals the all in*/
            int difference = Bet - Bet2;
            Betting_Add_On_Modifying_Money(&(Array_Of_Players[Index_SB]), difference); /* We add back the difference to the small blind if big blind all in is small than small blind all in */
            Did_Bet(Array_Of_Players,Index_BB,Bet2);
            Betting_Add_On_Modifying_Money(&(Array_Of_Players[Index_BB]), -Bet);
            Array_Of_Players[Index_BB].isAllin=1;
        }
    }

    /* We are done with the big blind betting*/




}
    

int main()
{
    PrintPokerBanner();

    int *Number_Of_Players =0; /* Initialisation */
    printf("\n \n How many players are present : ");
    scanf("%d", Number_Of_Players);
    getchar();
    Player Array_Of_Players[*Number_Of_Players]; /* Only used for the first round*/
    Definition_Of_All_Players(Array_Of_Players, *Number_Of_Players);
    
    /*------------------------------------------*/
    /* First round we'll be played here*/
    Initialisation_Roles(Array_Of_Players);
    for (int i=0; i<*Number_Of_Players;i++)
    {    
        Display_Of_Players(Array_Of_Players,i);
    }

    /*Insert whole game algorithm*/

    /* First round is now done*/
    /*--------------------------------------------*/
    Player *New_Array_Of_Players = malloc(sizeof(Player));
    New_Array_Of_Players = Verify_Players_Have_Money(Array_Of_Players,Number_Of_Players); /* We did update the array of players*/
    /*--------------------------------------------*/
    /* All the others round are played in here util only one player is remaining*/
    while (*Number_Of_Players >1)
    {
        Switch_Roles(New_Array_Of_Players,*Number_Of_Players);
        /* Insert Whole game algorithm*/

        Player *New_Array_Of_Players = malloc(sizeof(Player));
        New_Array_Of_Players = Verify_Players_Have_Money(Array_Of_Players,Number_Of_Players); /* We did update the array of players*/
    }




    
    /* Number of players has been updated and Array_Of_Players is updated*/
    
    
    free(New_Array_Of_Players);
    

    


    /*-----------------------------------------*/

    return 0;
}

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
    printf("\n %s's balance is %d and is Role is %s , Bet = %d  \n",(&Array_Of_Players[Index])->Name,((&Array_Of_Players[Index])->Money), (&Array_Of_Players[Index])->Role,(&Array_Of_Players[Index])->Bet);
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

void Show_Options()
{
    printf("\nPossible Actions :\n");
    printf("1. Raise\n");
    printf("2. Call\n");
    printf("3. Fold\n");
    printf("4. All-In\n");
    printf("Choose your action (1, 2, 3, 4) : ");
}

void Betting_Add_On_Modifying_Money(Player *Player_selected, int Bet)
{
    Add_Money(Player_selected, -Bet);
}

int Switch_Roles(Player *Array_Of_PLayer, int Number_Of_Player)
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
        return Index_BB+1;
    }
    else /* Means Index_BB is the last element of our array*/
    {
        strcpy(Array_Of_PLayer[0].Role,"Big Blind");
        return 0;
    }

    /*We have to check if all roles are allocated*/
    if (Number_Of_Player>=3) /* All roles should be present*/
    {
        
        int Index_One_Without_Roles;
        bool Dealer,SB,BB,Neutral;
        for (int i=0; i<Number_Of_Player; i++)
        {
            if (strcmp(Array_Of_PLayer[i].Role,"Dealer")==0)
            {
                Dealer = true;
            }
            else if (strcmp(Array_Of_PLayer[i].Role,"Small Blind")==0)
            {
                SB = true;
            }
            else if (strcmp(Array_Of_PLayer[i].Role,"Big Blind")==0)
            {
                BB = true;
            }
            else /* Role is neutral*/
            { 
                Neutral = true;
            }
            
        }
        if (Dealer && SB && BB)
        {
        }
        else
        {
            printf("There is an error");
            /* Should add that should assign missing roles to that neutral*/
        }
    }


    }



Player *Verify_Players_Have_Money(Player *Array_Of_Players, int *Number_of_Players)
{
    int New_number_of_players = *Number_of_Players;
    
    for (int i = 0; i < *Number_of_Players; i++) 
    {
        if (Array_Of_Players[i].Money == 0)
        {
            printf(" %s is dead ", Array_Of_Players[i].Name);
            Array_Of_Players[i].dead = 1;
            New_number_of_players--;
        }
    }
    
    Player *New_Array = malloc(New_number_of_players * sizeof(Player));

    int j = 0;  // New index for the new array
    for (int i = 0; i < *Number_of_Players; i++)
    {
        if (Array_Of_Players[i].Money != 0)
        {
            New_Array[j] = Array_Of_Players[i];  // Copies only the remaining players
            j++;
        }
    }

    *Number_of_Players = New_number_of_players;
    return New_Array;
}



void Did_Bet(Player *Array_Of_Players, int Index_the_one_betting, int Bet)
{
    Array_Of_Players[Index_the_one_betting].Bet = Bet;
}

int All_Players_Equals(Player *Array_Of_Players, int Number_Of_Player)
{
    int Bet = Array_Of_Players[0].Bet;
    int increment;
    for (int i=0; i<Number_Of_Player; i++)
    {
        if (Array_Of_Players[i].Bet != Bet && (strcmp(Array_Of_Players[i].State,"Fold")!=0))
        {
            increment++;
        }
    }
    if (increment == Number_Of_Player-1){
        return 1;
    }
    return 0;
}


void Blind_Betting(Player *Array_Of_Players, int Number_Of_Players, int Small_Blind, int *Index_SB, int *Index_BB, int *Bet, int *Pot)
{
    Verify_Players_Have_Money(Array_Of_Players, &Number_Of_Players);
    for (int i=0; i<Number_Of_Players;i++)
    {    
        if (strcmp(Array_Of_Players[i].Role,"Small Blind")==0)
        {
            *Index_SB =i;
        }
        if (strcmp(Array_Of_Players[i].Role,"Big Blind")==0)
        {
            *Index_BB =i;
        }
    }
   
    printf("\n -------------------- \n");
    printf("\n Small Blind is $%d \n", Small_Blind);
    printf("\n -------------------- \n");
    
    /* We make the Small Blind pay*/
    if (Array_Of_Players[*Index_SB].Money > Small_Blind )
    {
        // No worries we just bet as usual
        *Bet = Small_Blind;
        Did_Bet(Array_Of_Players,*Index_SB,*Bet);
        *Pot += *Bet;
        Betting_Add_On_Modifying_Money(&(Array_Of_Players[*Index_SB]),*Bet);
    }
    else  /*Means he's all in beacause verifying players have money would have deleted the mad before this function*/
    {
        *Bet = Array_Of_Players[*Index_SB].Money;
        Did_Bet(Array_Of_Players,*Index_SB,*Bet);
        *Pot += *Bet;
        Array_Of_Players[*Index_SB].isAllin=1;
        Betting_Add_On_Modifying_Money(&(Array_Of_Players[*Index_SB]), Array_Of_Players[*Index_SB].Money);
    }
    /*Small Blind is done betting for now*/

    /* We make big blind pay now*/
    if (Array_Of_Players[*Index_SB].isAllin==0)
    {
        if (Array_Of_Players[*Index_BB].Money > ((*Bet)<<1))
        {
            *Bet = (*Bet)<<1;
            Did_Bet(Array_Of_Players,*Index_BB,*Bet);
            *Pot += *Bet;
            Betting_Add_On_Modifying_Money(&(Array_Of_Players[*Index_BB]), *Bet);
        }
        else
        {
            *Bet = Array_Of_Players[*Index_BB].Money;
            Did_Bet(Array_Of_Players,*Index_BB,*Bet);
            *Pot += *Bet;
            Array_Of_Players[*Index_BB].isAllin=1;
            Betting_Add_On_Modifying_Money(&(Array_Of_Players[*Index_BB]), Array_Of_Players[*Index_BB].Money);
        }
    }
    else
    {
        /* The bet does not change*/
        if (Array_Of_Players[*Index_BB].Money > (((*Bet)<<1)))
        {
            *Bet = ((*Bet)<<1);
            Did_Bet(Array_Of_Players,*Index_BB,*Bet);
            *Pot += *Bet;
            Betting_Add_On_Modifying_Money(&(Array_Of_Players[*Index_BB]), *Bet);
        }
        else /* Covers cases if BB has as much money as the SB or less*/
        {
            int Bet2 = Array_Of_Players[*Index_BB].Money; /* Changes nothing if whole money equals the all in*/
            int difference = *Bet - Bet2;
            Betting_Add_On_Modifying_Money(&(Array_Of_Players[*Index_SB]), -difference); /* We add back the difference to the small blind if big blind all in is small than small blind all in */
            Array_Of_Players[*Index_SB].Money += difference;
            *Bet=Bet2;
            *Pot -= difference;
            Did_Bet(Array_Of_Players,*Index_BB,*Bet);
            *Pot += *Bet;
            Betting_Add_On_Modifying_Money(&(Array_Of_Players[*Index_BB]), *Bet);
            Array_Of_Players[*Index_BB].isAllin=1;
        }
    }

    /* We are done with the big blind betting*/
}

int Reset_All_Bets_Player_And_Gen(Player *Array_Of_Players, int Number_Of_Player) /* return the base bet for the next round which is 0*/
{
    for (int i=0; i<Number_Of_Player; i++)
        Array_Of_Players[i].Bet=0;
    return 0;
    
}



void Usual_Betting(Player *Array_Of_Players, int Number_Of_Players, int Small_Blind, int *Bet, int Index_BB, int *Pot)
{
    /*  Small Blind laways bet first (could implement the guy raising being the first one to bid) */
    int Option_chosen,Raise;
    
    /* Now all the players got to bet*/
    int currentPlayer = (Index_BB + 1) % Number_Of_Players;  // Starts right after big blind


    int Actually_betted;
    for (int i=0; i<Number_Of_Players;i++) /* for is there in case of the first ones fold or check cause all of theirs moeny will be the same but we still have to ask everyone to place theirs bets*/
    {
        if (strcmp(Array_Of_Players[currentPlayer].State, "Fold") != 0 || Array_Of_Players[currentPlayer].isAllin== 0) {
            printf("\n--- %s 's turn to play ---\n", Array_Of_Players[currentPlayer].Name);
            printf("The current bet is $%d \n", *Bet);
            Display_Of_Players(Array_Of_Players, currentPlayer);
            Show_Options();
            scanf("%d", &Option_chosen);

            switch (Option_chosen) {
                case 3:
                    strcpy(Array_Of_Players[currentPlayer].State, "Fold");
                    break;
                case 1:
                    // Raise
                    printf("How much do you want to raise?: ");
                    scanf("%d", &Raise);
                    *Bet += Raise;  // Increases the bet
                    Actually_betted = ((*Bet)-Array_Of_Players[currentPlayer].Bet);
                    Did_Bet(Array_Of_Players, currentPlayer, *Bet);
                    *Pot += Actually_betted;
                    Betting_Add_On_Modifying_Money(&(Array_Of_Players[currentPlayer]), Actually_betted);
                    break;
                case 2:
                    // Call

                    
                    Actually_betted = ((*Bet)-Array_Of_Players[currentPlayer].Bet); // In case of a previous bet has been placed
                    Did_Bet(Array_Of_Players, currentPlayer,*Bet);
                    /* If they already have a bet, they should not */
                    *Pot +=Actually_betted;
                    Betting_Add_On_Modifying_Money(&(Array_Of_Players[currentPlayer]), Actually_betted);
                    break;
                case 4:
                    // All-in
                    *Bet = Array_Of_Players[currentPlayer].Money;
                    Did_Bet(Array_Of_Players, currentPlayer, *Bet);
                    *Pot += *Bet;
                    Betting_Add_On_Modifying_Money(&(Array_Of_Players[currentPlayer]), *Bet);
                    Array_Of_Players[currentPlayer].isAllin = 1;
                    break;
                default:
                    printf("Invalid option chosen\n");
                    break;
            }
            currentPlayer = (currentPlayer + 1) % Number_Of_Players;
        }
    }
        

    while (All_Players_Equals(Array_Of_Players, Number_Of_Players)!=0)
    {
        if (strcmp(Array_Of_Players[currentPlayer].State, "Fold") != 0) {
            printf("\n--- %s 's turn to play ---\n", Array_Of_Players[currentPlayer].Name);
            printf("The current bet is $%d \n", *Bet);
            Display_Of_Players(Array_Of_Players, currentPlayer);
            Show_Options();
            scanf("%d", &Option_chosen);

            switch (Option_chosen) {
                case 3:
                    strcpy(Array_Of_Players[currentPlayer].State, "Fold");
                    break;
                case 1:
                    // Raise
                    printf("How much do you want to raise?: ");
                    scanf("%d", &Raise);
                    *Bet += Raise;  // Increases the bet
                    Actually_betted = ((*Bet)-Array_Of_Players[currentPlayer].Bet);
                    Did_Bet(Array_Of_Players, currentPlayer, *Bet);
                    *Pot += Actually_betted;
                    Betting_Add_On_Modifying_Money(&(Array_Of_Players[currentPlayer]), Actually_betted);
                    break;
                case 2:
                    // Call

                    
                    Actually_betted = ((*Bet)-Array_Of_Players[currentPlayer].Bet); // In case of a previous bet has been placed
                    Did_Bet(Array_Of_Players, currentPlayer,*Bet);
                    /* If they already have a bet, they should not */
                    *Pot +=Actually_betted;
                    Betting_Add_On_Modifying_Money(&(Array_Of_Players[currentPlayer]), Actually_betted);
                    break;
                case 4:
                    // All-in
                    *Bet = Array_Of_Players[currentPlayer].Money;
                    Did_Bet(Array_Of_Players, currentPlayer, *Bet);
                    *Pot += *Bet;
                    Betting_Add_On_Modifying_Money(&(Array_Of_Players[currentPlayer]), *Bet);
                    Array_Of_Players[currentPlayer].isAllin = 1;
                    break;
                default:
                    printf("Invalid option chosen\n");
                    break;
            }
            currentPlayer = (currentPlayer + 1) % Number_Of_Players;
            
        }
        else {
            currentPlayer = (currentPlayer + 1) % Number_Of_Players;
            
            return;
        }
    };
    
    // All players did place their bets

}


void whowon(Player *Array_Of_Players, int Pot, int Number_Of_Players) {
    char winner_name[SIZE_NAME];
    int test = 0;
    int index = -1;

    while (test == 0) {
        printf("Who won this round ? \n");
            scanf("%s",winner_name);
            winner_name[strcspn(winner_name, "\n")] = '\0';  

            for (int i = 0; i < Number_Of_Players; i++) {
                if (strcmp(Array_Of_Players[i].Name, winner_name) == 0) {
                    test = 1;
                    index = i;  
                    break;
                }
            }

            if (test == 1) {
                Array_Of_Players[index].Money += Pot;  
                printf("\n\n$-------------------------$\n\n");
                printf("%s won this round and his balance is now %d\n", Array_Of_Players[index].Name, Array_Of_Players[index].Money);
                printf("\n\n$-------------------------$\n\n");
                sleep(5);
            } else {
                printf("Enter a valid name please\n");
            }
        
    }
}

int Number_Of_Allin(Player* Array_Of_Players, int Number_Of_Players){
    int nb_allin=0;
    for (int i=0;i<Number_Of_Players;i++){
        if (Array_Of_Players[i].isAllin==1){
            nb_allin++;
        }
    }
    return nb_allin;
}

int Number_Of_Players_Still_In(Player *Array_Of_Players,int Number_Of_Players)
{
    int Output=Number_Of_Players;
    for (int i=0; i<Number_Of_Players; i++)
    {
        if (strcmp(Array_Of_Players[i].State,"Fold")==0)
        {
            Output--;
        }

    }
    return Output;
}

void rounds(Player *Array_Of_Players, int Number_Of_Players, int Small_Blind, int *Index_SB, int *Index_BB, int *Bet, int *Pot, char **Round, int Rounds_Played) {
    int Players_Not_Folded = Number_Of_Players;
    
    Blind_Betting(Array_Of_Players, Number_Of_Players, Small_Blind, Index_SB, Index_BB, Bet, Pot);
    
    while (Players_Not_Folded > 1 && Rounds_Played <= NUMBER_OF_ROUNDS -1 ) {    
        
            printf("\n\n ---------- %s -------------- \n \n", Round[Rounds_Played]);
            printf("\n Pot : $%d\n", *Pot);
            
            Usual_Betting(Array_Of_Players, Number_Of_Players, Small_Blind, Bet, *Index_BB, Pot);
            
            for (int i = 0; i < Number_Of_Players; i++) {
                Display_Of_Players(Array_Of_Players, i);
            }
            
            printf("\n Pot : $%d\n", *Pot);
            
            *Bet = Reset_All_Bets_Player_And_Gen(Array_Of_Players, Number_Of_Players);       
            Players_Not_Folded = Number_Of_Players_Still_In(Array_Of_Players, Number_Of_Players);
            (Rounds_Played)++;
         
            
            
        
    }
    
    // Si plus d'un joueur est en jeu après tous les rounds, on demande qui a gagné
    whowon(Array_Of_Players, *Pot, Number_Of_Players); //à changer de place uniquement si +1 joueurs à la fin
    
}



int main()
{
    PrintPokerBanner();
    int Small_Blind = 10;
    int Number_Of_Players = 0;
    int Index_SB,Index_BB,Bet, Players_Not_Folded;
    int Pot=0,Rounds_Played=0;
    char *Round[NUMBER_OF_ROUNDS]={"Preflop","Flop","Turn","River"};
    
    printf("\n \n How many players are present : ");
    scanf("%d", &Number_Of_Players);
    getchar();
    Player *Array_Of_Players = (Player *) malloc(Number_Of_Players * sizeof(Player));

    
    
    Definition_Of_All_Players(Array_Of_Players, Number_Of_Players);
     

    //Structure quite weird i have to agree, this part was training to use only static tables that's why it's not in the loop, it's useful only for the first game

    // First round
    Initialisation_Roles(Array_Of_Players);

    for (int i = 0; i < Number_Of_Players; i++)
    {
        Display_Of_Players(Array_Of_Players, i);
    }
    sleep(3); // To be able to see the players
    
    rounds(Array_Of_Players, Number_Of_Players, Small_Blind, &Index_SB, &Index_BB, &Bet, &Pot, Round, Rounds_Played);


    
    // End of First game

    // All of the next games can now begin ( we use dynamic tables because of the possibility of someone dying and of so we need a New Table)
    Player *New_Array_Of_Players;
    New_Array_Of_Players = Verify_Players_Have_Money(Array_Of_Players, &Number_Of_Players);
    while (Number_Of_Players >1)
    {
       
       Pot = 0; 
       Switch_Roles(New_Array_Of_Players,Number_Of_Players);
       Rounds_Played = 0;
       printf("\n------------- Roles have been switched ------------ \n");
       for (int i = 0; i < Number_Of_Players; i++)
        {
            
            Display_Of_Players(New_Array_Of_Players, i);
        }
        Blind_Betting(New_Array_Of_Players,Number_Of_Players,Small_Blind,&Index_SB,&Index_BB,&Bet,&Pot);
        Players_Not_Folded = Number_Of_Players;
        while( Players_Not_Folded>1 && Rounds_Played <= NUMBER_OF_ROUNDS-1)
        {    
            printf("\n\n ---------- %s -------------- \n \n", Round[Rounds_Played]);
            printf("\n Pot : $%d\n",Pot);
            Usual_Betting(New_Array_Of_Players,Number_Of_Players,Small_Blind,&Bet,Index_BB,&Pot);
            for (int i = 0; i < Number_Of_Players; i++)
            {
                Display_Of_Players(New_Array_Of_Players, i);
            }
            printf("\n Pot : %d\n",Pot);
            Bet = Reset_All_Bets_Player_And_Gen(New_Array_Of_Players,Number_Of_Players);
            Players_Not_Folded = Number_Of_Players_Still_In(New_Array_Of_Players, Number_Of_Players);
            Rounds_Played++;
            //clearTerminal();
        }
        whowon(New_Array_Of_Players, Pot,Number_Of_Players);
        New_Array_Of_Players = Verify_Players_Have_Money(Array_Of_Players, &Number_Of_Players);
    }




        
        





    
    free(New_Array_Of_Players);
    // That's to add after the final bet on the river
    

    return 0;
}


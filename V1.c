#include "initialisations.h"
#include "constantes.h" 

Player* Role_To_Previous_Player(Player *Array_Of_Players, int Index_Player_Being_Deleted, int Number_Of_Players, char *Role_To_Allocate) {
    int Index_Prior = Index_Player_Being_Deleted - 1;
    char Temporary_Role[SIZE_ROLE];
    printf("\n Le role à allouer est %s", Role_To_Allocate);

    printf("\nDébut de Role_To_Previous_Player avec affichage des rôles :\n");
    for (int i = 0; i < Number_Of_Players; i++) {
        Display_Of_Players(Array_Of_Players, i);
    }
    sleep(4);

    if (Number_Of_Players > 3) {
        // Gestion standard pour au moins 3 joueurs
        if (Index_Prior < 0) {
            // Si l'index est en dehors des limites, retourne au dernier joueur
            Index_Prior = Number_Of_Players - 1;
        }

        printf("\nControle du joueur %s\n", Array_Of_Players[Index_Prior].Name);
        if (strcmp(Array_Of_Players[Index_Prior].Role, "Neutre") == 0) {
            // Assigne le rôle cible et met le joueur supprimé en Neutre
            printf("\n Condition de fin \n");
            printf("Le role est %s", Role_To_Allocate);
            printf("\n On met ce role a : %s", Array_Of_Players[Index_Prior].Name);
            strcpy(Array_Of_Players[Index_Prior].Role, Role_To_Allocate);
            printf("\nOn verifie que bien update (joueur avant) \n");
            Display_Of_Players(Array_Of_Players,Index_Prior);
            sleep(1);
            return Array_Of_Players;
        } else {
            // Transfert le rôle actuel pour continuer la boucle
            strcpy(Temporary_Role, Array_Of_Players[Index_Prior].Role);
            printf("\n Tempo : %s", Temporary_Role);
            strcpy(Array_Of_Players[Index_Prior].Role, Role_To_Allocate);
            return Role_To_Previous_Player(Array_Of_Players, Index_Prior, Number_Of_Players, Temporary_Role);
        }
    } 
    else 
    {
        // Cas où le nombre de joueurs est inférieur à 3
        if (Index_Prior < 0) {
            // Si l'index est en dehors des limites, retourne au dernier joueur
            Index_Prior = Number_Of_Players - 1;
        }

        printf("\nControle du joueur %s\n", Array_Of_Players[Index_Prior].Name);
        if (strcmp(Array_Of_Players[Index_Prior].Role, "Big Blind") == 0) {
            // Assigne le rôle cible et met le joueur supprimé en Neutre
            printf("\n Condition de fin \n");
            printf("Le role est %s", Role_To_Allocate);
            printf("\n On met ce role a : %s", Array_Of_Players[Index_Prior].Name);
            strcpy(Array_Of_Players[Index_Prior].Role, Role_To_Allocate);
            printf("\nOn verifie que bien update (joueur avant) \n");
            Display_Of_Players(Array_Of_Players,Index_Prior);
            sleep(3);
            return Array_Of_Players;
        } else {
            // Transfert le rôle actuel pour continuer la boucle
            strcpy(Temporary_Role, Array_Of_Players[Index_Prior].Role);
            printf("\n Tempo : %s", Temporary_Role);
            strcpy(Array_Of_Players[Index_Prior].Role, Role_To_Allocate);
            return Role_To_Previous_Player(Array_Of_Players, Index_Prior, Number_Of_Players, Temporary_Role);
        }
    }
}



Player *Verify_Players_Have_Money(Player *Array_Of_Players, int *Number_of_Players)
{
    int New_number_of_players = *Number_of_Players;
    
    for (int i = 0; i < *Number_of_Players; i++) 
    {
        if (Array_Of_Players[i].Money <= 0)
        {
            printf(" %s is dead ", Array_Of_Players[i].Name);
            Array_Of_Players[i].dead = 1;
            New_number_of_players--;
            // We're checking if a role is present to make sure we don't delete one
            if (*Number_of_Players >3) {
                if (strcmp(Array_Of_Players[i].Role,"Neutre") != 0)
                {
                    printf("\n Player to delete has a role \n");
                    /*We foward is role to the previous people*/
                    Array_Of_Players = Role_To_Previous_Player(Array_Of_Players,i,*Number_of_Players, Array_Of_Players[i].Role);
                    for (int j=0; j<*Number_of_Players; j++)
                        Display_Of_Players(Array_Of_Players,j);
                }
            }
            else
            {
                if (strcmp(Array_Of_Players[i].Role,"Big Blind") != 0)
                {
                    printf("\n Player to delete has a role \n");
                    /*We foward is role to the previous people*/
                    Array_Of_Players = Role_To_Previous_Player(Array_Of_Players,i,*Number_of_Players, Array_Of_Players[i].Role);
                    for (int j=0; j<*Number_of_Players; j++)
                        Display_Of_Players(Array_Of_Players,j);
                }
            }


        }
    }
    
    Player *New_Array = malloc(New_number_of_players * sizeof(Player));

    int j = 0;  // New index for the new array
    for (int i = 0; i < *Number_of_Players; i++)
    {
        if (Array_Of_Players[i].Money > 0)
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

int All_Players_Equals(Player *Array_Of_Players, int Number_Of_Player, int* Bet)
{
    
    int increment=0;
    for (int i=0; i<Number_Of_Player; i++)
    {
        if (Array_Of_Players[i].Bet == *Bet || (strcmp(Array_Of_Players[i].State,"Fold")==0))
        {
            increment++;
        }
    }
    if (increment == Number_Of_Player){
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

void Reset_AllIn_Folds(Player *Array_Of_Player, int Number_Of_Players)
{
    for (int i=0; i<Number_Of_Players; i++)
    {
        Array_Of_Player[i].isAllin =0;
        strcpy(Array_Of_Player[i].State, "N"); /* N for neutral*/
    }
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

void Check_If_Is_All_In(Player *Ptr_Player)
{
    if (Ptr_Player->Money == 0)
    {
        Ptr_Player->isAllin = 1;
        printf("\n\n %s IS ALL IN \n \n", Ptr_Player->Name);
    }
}

void Usual_Betting(Player *Array_Of_Players, int Number_Of_Players, int Small_Blind, int *Bet, int Index_BB, int *Pot, int *currentPlayer)
{
    /*  Small Blind laways bet first (could implement the guy raising being the first one to bid) */
    int Option_chosen,Raise;
    
    /* Now all the players got to bet*/
     // Starts right after big blind
    int number_folds=0;
    int Actually_betted;
    for (int i=0; i<Number_Of_Players;i++) /* for is there in case of the first ones fold or check cause all of theirs moeny will be the same but we still have to ask everyone to place theirs bets*/
    {
        if (strcmp(Array_Of_Players[*currentPlayer].State, "Fold") != 0 && Array_Of_Players[*currentPlayer].isAllin== 0) 
        {
            printf("\n--- %s 's turn to play ---\n", Array_Of_Players[*currentPlayer].Name);
            printf("The current bet is $%d \n", *Bet);
            Display_Of_Players(Array_Of_Players, *currentPlayer);
            Show_Options();
            scanf("%d", &Option_chosen);

            switch (Option_chosen) {
                case 3:
                    strcpy(Array_Of_Players[*currentPlayer].State, "Fold");
                    number_folds++;
                    break;
                case 1:
                    // Raise
                    printf("How much do you want to raise?: ");
                    scanf("%d", &Raise);
                    while (Raise<0){
                        printf("\nPlease enter a positive value :");
                        scanf("%d", &Raise);
                    }
                    *Bet += Raise;  // Increases the bet
                    Actually_betted = ((*Bet)-Array_Of_Players[*currentPlayer].Bet);
                    Did_Bet(Array_Of_Players, *currentPlayer, *Bet);
                    *Pot += Actually_betted;
                    Betting_Add_On_Modifying_Money(&(Array_Of_Players[*currentPlayer]), Actually_betted);
                    Check_If_Is_All_In(&(Array_Of_Players[*currentPlayer]));
                    break;
                case 2:
                    // Call

                    
                    Actually_betted = ((*Bet)-Array_Of_Players[*currentPlayer].Bet); // In case of a previous bet has been placed
                    Did_Bet(Array_Of_Players, *currentPlayer,*Bet);
                    /* If they already have a bet, they should not */
                    *Pot +=Actually_betted;
                    Betting_Add_On_Modifying_Money(&(Array_Of_Players[*currentPlayer]), Actually_betted);
                    Check_If_Is_All_In(&(Array_Of_Players[*currentPlayer]));
                    break;
                case 4:
                    // All-in
                    Array_Of_Players[*currentPlayer].Money += Array_Of_Players[*currentPlayer].Bet; // We reset the money
                    *Pot -= Array_Of_Players[*currentPlayer].Bet;
                    *Bet = Array_Of_Players[*currentPlayer].Money;
                    Did_Bet(Array_Of_Players, *currentPlayer, *Bet);
                    *Pot += *Bet;
                    Betting_Add_On_Modifying_Money(&(Array_Of_Players[*currentPlayer]), *Bet);
                    Check_If_Is_All_In(&(Array_Of_Players[*currentPlayer]));
                    break;
                default:
                    printf("Invalid option chosen\n");
                    break;
            }
        }
        *currentPlayer = (*currentPlayer + 1) % Number_Of_Players;
        if (number_folds==Number_Of_Players-1){
            Array_Of_Players[*currentPlayer].Money += *Pot;  
                printf("\n\n$-------------------------$\n\n");
                printf("%s won this round and his balance is now %d\n", Array_Of_Players[*currentPlayer].Name, Array_Of_Players[*currentPlayer].Money);
                printf("\n\n$-------------------------$\n\n");
                sleep(5);
            return;
        }
    }
    
    while (All_Players_Equals(Array_Of_Players, Number_Of_Players, Bet)==0)
    {
        if (strcmp(Array_Of_Players[*currentPlayer].State, "Fold") != 0) {
            printf("\n--- %s 's turn to play ---\n", Array_Of_Players[*currentPlayer].Name);
            printf("The current bet is $%d \n", *Bet);
            Display_Of_Players(Array_Of_Players, *currentPlayer);
            Show_Options();
            scanf("%d", &Option_chosen);

            switch (Option_chosen) {
                case 3:
                    strcpy(Array_Of_Players[*currentPlayer].State, "Fold");
                    number_folds++;
                    break;
                case 1:
                    // Raise
                    printf("How much do you want to raise?: ");
                    scanf("%d", &Raise);
                    while (Raise<0){
                        printf("\nPlease enter a positive value :");
                        scanf("%d", &Raise);
                    }
                    *Bet += Raise;  // Increases the bet
                    Actually_betted = ((*Bet)-Array_Of_Players[*currentPlayer].Bet);
                    Did_Bet(Array_Of_Players, *currentPlayer, *Bet);
                    *Pot += Actually_betted;
                    Betting_Add_On_Modifying_Money(&(Array_Of_Players[*currentPlayer]), Actually_betted);
                    Check_If_Is_All_In(&(Array_Of_Players[*currentPlayer]));
                    break;
                case 2:
                    // Call

                    
                    Actually_betted = ((*Bet)-Array_Of_Players[*currentPlayer].Bet); // In case of a previous bet has been placed
                    Did_Bet(Array_Of_Players, *currentPlayer,*Bet);
                    /* If they already have a bet, they should not */
                    *Pot +=Actually_betted;
                    Betting_Add_On_Modifying_Money(&(Array_Of_Players[*currentPlayer]), Actually_betted);
                    Check_If_Is_All_In(&(Array_Of_Players[*currentPlayer]));
                    break;
                case 4:
                    // All-in
                    Array_Of_Players[*currentPlayer].Money += Array_Of_Players[*currentPlayer].Bet;
                    *Pot -= Array_Of_Players[*currentPlayer].Bet;
                    *Bet = Array_Of_Players[*currentPlayer].Money;
                    Did_Bet(Array_Of_Players, *currentPlayer, *Bet);
                    *Pot += *Bet;
                    Betting_Add_On_Modifying_Money(&(Array_Of_Players[*currentPlayer]), *Bet);
                    Check_If_Is_All_In(&(Array_Of_Players[*currentPlayer]));
                    break;
                default:
                    printf("Invalid option chosen\n");
                    break;
            }
            *currentPlayer = (*currentPlayer + 1) % Number_Of_Players;
            
        }
        else {
            *currentPlayer = (*currentPlayer + 1) % Number_Of_Players;
            
            
        }
        if (number_folds==Number_Of_Players-1){
            Array_Of_Players[*currentPlayer].Money += *Pot;  
                printf("\n\n$-------------------------$\n\n");
                printf("%s won this round and his balance is now %d\n", Array_Of_Players[*currentPlayer].Name, Array_Of_Players[*currentPlayer].Money);
                printf("\n\n$-------------------------$\n\n");
                sleep(5);
            return;
        }
    }
    
    
    // All players did place their bets

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

void rounds(Player *Array_Of_Players, int Number_Of_Players, int Small_Blind, int *Index_SB, int *Index_BB, int *Bet, int *Pot, char **Round, int Rounds_Played, int Index_Dealer) {
    int Players_Not_Folded = Number_Of_Players;
    int currentPlayer = (Index_Dealer+3) % Number_Of_Players;
    
    Blind_Betting(Array_Of_Players, Number_Of_Players, Small_Blind, Index_SB, Index_BB, Bet, Pot);
    
    while (Players_Not_Folded > 1 && Rounds_Played <= NUMBER_OF_ROUNDS -1) {    
        
        printf("\n\n ---------- %s -------------- \n \n", Round[Rounds_Played]);
        printf("\n Pot : $%d\n", *Pot);
        
        Usual_Betting(Array_Of_Players, Number_Of_Players, Small_Blind, Bet, *Index_BB, Pot, &currentPlayer);
        currentPlayer=(*Index_SB)%Number_Of_Players;
        
        for (int i = 0; i < Number_Of_Players; i++) {
            Display_Of_Players(Array_Of_Players, i);
        }
        
        printf("\n Pot : $%d\n", *Pot);
        
        *Bet = Reset_All_Bets_Player_And_Gen(Array_Of_Players, Number_Of_Players);       
        Players_Not_Folded = Number_Of_Players_Still_In(Array_Of_Players, Number_Of_Players);
        
        Rounds_Played++;  
        printf("Played");          
    }
    if (Players_Not_Folded>1){
        whowon(Array_Of_Players, *Pot,Number_Of_Players);
    }

}

void Change_Roles_Manually(Player *Array_Of_Players, int Number_Of_Players)
{
    char Name_To_Change[SIZE_NAME];
    int Role,Index_Save;
    printf("\n--- Here are the players (should be an issue in the roles) ---\n");
    for (int i=0; i<Number_Of_Players; i++)
    {
        Display_Of_Players(Array_Of_Players,i);
    }
    printf("\n Which player should have is role changed :\n");
    fgets(Name_To_Change,SIZE_NAME,stdin);
    Name_To_Change[strcspn(Name_To_Change, "\n")] = '\0';
    for (int j=0; j<Number_Of_Players; j++)
    {
        if (strcmp(Array_Of_Players[j].Name, Name_To_Change))
        {
            Index_Save=j;
        }

    }
    printf("\n What Should be his Role ? (1 = Small Blind, 2 = Big Blind, 3 = Dealer, 4 = Neutral)");
    scanf("%d", &Role);
    switch (Role)
    {
    case 1:
        strcpy(Array_Of_Players[Index_Save].Role, "Small Blind");
        break;
    case 2:
        strcpy(Array_Of_Players[Index_Save].Role,"Big Blind");
        break;
    case 3:
        strcpy(Array_Of_Players[Index_Save].Role,"Dealer");
        break;
    case 4:
        strcpy(Array_Of_Players[Index_Save].Role,"N");
        break;
    default:
        break;
    }
}





int Verify_Roles_Are_Presents(Player *Array_Of_Players, int Number_Of_Players)
{
    int Count_Of_Roles = 0;
    for (int i=0; i<Number_Of_Players ; i++)
    {
        if (strcmp(Array_Of_Players[i].Role,"N") != 0)
        {
            Count_Of_Roles++;
            printf("%d",Count_Of_Roles);
        }
    }
    if (Count_Of_Roles<3 && Number_Of_Players>=3)
    {
        printf("\n There seems to be an issue with the new roles, please make sure you resolve the issue \n");
        return 1;

    }
    else if (Number_Of_Players <3)
    {
        if(Count_Of_Roles!=Number_Of_Players)
        {
            printf("\n There seems to be an issue with the new roles, please make sure you resolve the issue \n");
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if(Count_Of_Roles == 3)
    {
        return 0;
    }
    else
    {
        printf("Weird thing Happening Count = %d and Number = %d", Count_Of_Roles,Number_Of_Players);
        return 1;
    }

}




int main()
{
    PrintPokerBanner();
    int Small_Blind = 10;
    int Number_Of_Players = 0;
    int Index_SB,Index_BB,Bet, Players_Not_Folded,Answer = -1;
    int Pot=0,Rounds_Played=0;
    int Index_Dealer=0;
    char *Round[NUMBER_OF_ROUNDS]={"Preflop","Flop","Turn","River"};
    printf("\n \n How many players are present : ");
    scanf("%d", &Number_Of_Players);
    getchar();
    Player *Array_Of_Players = (Player *) malloc(Number_Of_Players * sizeof(Player));
    Player *New_Array_Of_Players;
    Definition_Of_All_Players(Array_Of_Players, Number_Of_Players); // For the following rounds
    // First round
    Initialisation_Roles(Array_Of_Players);
    for (int i = 0; i < Number_Of_Players; i++)
    {
        Display_Of_Players(Array_Of_Players, i);
    }
    sleep(3); // To be able to see the players
    rounds(Array_Of_Players, Number_Of_Players, Small_Blind, &Index_SB, &Index_BB, &Bet, &Pot, Round, Rounds_Played, Index_Dealer); // Needs to be outside of the loop bcause we're using Array_Of_Players but then we'll uses New_Array
    Reset_AllIn_Folds(Array_Of_Players, Number_Of_Players);
    New_Array_Of_Players = Verify_Players_Have_Money(Array_Of_Players, &Number_Of_Players); // The same Here
    while (Number_Of_Players >1)
    {
        
        Pot = 0;
        Index_Dealer=Switch_Roles(New_Array_Of_Players,Number_Of_Players)%Number_Of_Players;
        printf("\n------------- Roles have been switched ------------ \n");
        for (int i = 0; i < Number_Of_Players; i++)
        {    
            Display_Of_Players(New_Array_Of_Players, i);
        }
        printf("\n Do you see an issue ? (0 for yes) :");
        scanf("%d",&Answer);
        getchar();
        while (Answer ==0)
        {
            Change_Roles_Manually(New_Array_Of_Players, Number_Of_Players);
            printf("\n Do you see an issue ? (0 for yes) :");
            scanf("%d",&Answer);
            getchar();
        }
        
        Rounds_Played = 0;
        
        break_round(&Small_Blind);
        rounds(New_Array_Of_Players, Number_Of_Players, Small_Blind, &Index_SB, &Index_BB, &Bet, &Pot, Round, Rounds_Played, Index_Dealer);
        Reset_AllIn_Folds(New_Array_Of_Players, Number_Of_Players);
        New_Array_Of_Players = Verify_Players_Have_Money(New_Array_Of_Players, &Number_Of_Players);
    }


    free(New_Array_Of_Players);
    // That's to add after the final bet on the river
    

    return 0;
}

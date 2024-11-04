#include "Rounds.h"

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
    if (Number_Of_Players>2)
    {
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
    }

    /* We are done with the big blind betting*/
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



void rounds(Player *Array_Of_Players, int Number_Of_Players, int Small_Blind, int *Index_SB, int *Index_BB, int *Bet, int *Pot, char **Round, int Rounds_Played, int Index_Dealer) {
    int Players_Not_Folded = Number_Of_Players;
    int currentPlayer;
    if (Number_Of_Players>2)
    {
        currentPlayer = (Index_Dealer+3) % Number_Of_Players;
    }
    else
    {
        currentPlayer = Index_Dealer;
    }
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
#include "initialisations.h"
#include "constantes.h" 
#include "Players_Management.h"
#include "Rounds.h"







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

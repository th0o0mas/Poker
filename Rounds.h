#include "constantes.h"
#include "initialisations.h"
#include "Players_Management.h"

void Did_Bet(Player *Array_Of_Players, int Index_the_one_betting, int Bet);
int All_Players_Equals(Player *Array_Of_Players, int Number_Of_Player, int* Bet);
void Blind_Betting(Player *Array_Of_Players, int Number_Of_Players, int Small_Blind, int *Index_SB, int *Index_BB, int *Bet, int *Pot);
void Usual_Betting(Player *Array_Of_Players, int Number_Of_Players, int Small_Blind, int *Bet, int Index_BB, int *Pot, int *currentPlayer);
int Number_Of_Allin(Player* Array_Of_Players, int Number_Of_Players);
void rounds(Player *Array_Of_Players, int Number_Of_Players, int Small_Blind, int *Index_SB, int *Index_BB, int *Bet, int *Pot, char **Round, int Rounds_Played, int Index_Dealer);
void Change_Roles_Manually(Player *Array_Of_Players, int Number_Of_Players);
int Verify_Roles_Are_Presents(Player *Array_Of_Players, int Number_Of_Players);
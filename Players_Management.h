#include "constantes.h"
#include "initialisations.h"

void Add_Money(Player *Player_Selected, int Money_Incremented);
void Show_Options(void);
void Betting_Add_On_Modifying_Money(Player *Player_selected, int Bet);
Player* Role_To_Previous_Player(Player *Array_Of_Players, int Index_Player_Being_Deleted, int Number_Of_Players, char *Role_To_Allocate);
Player *Verify_Players_Have_Money(Player *Array_Of_Players, int *Number_of_Players);
int Reset_All_Bets_Player_And_Gen(Player *Array_Of_Players, int Number_Of_Player);
void Reset_AllIn_Folds(Player *Array_Of_Player, int Number_Of_Players);
void whowon(Player *Array_Of_Players, int Pot, int Number_Of_Players);
void Check_If_Is_All_In(Player *Ptr_Player);
int Number_Of_Players_Still_In(Player *Array_Of_Players,int Number_Of_Players);
int Switch_Roles(Player *Array_Of_Players, int Number_Of_Players);
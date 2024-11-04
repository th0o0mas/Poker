#ifndef INITIALISATIONS_H
#define INITIALISATIONS_H
#include "constantes.h"
void clearTerminal(void);
void PrintPokerBanner(void);
void Initialisation_Roles(Player *Array_Of_Players, int Number_Of_Players);
void Definition_Of_All_Players(Player *Array_Of_Player, int Players_In_Game);
void Initialization_Of_A_Player(char *Name, int Money, char *Role_g, char *State_g, Player *Player_Yet_To_Initialise);
void Display_Of_Players(Player *Array_Of_Players, int Index);
void break_round(int *SB);


#endif
#include "Players_Management.h"


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
    int Index_Of_Dead_P;
    
    for (int i = 0; i < *Number_of_Players; i++) 
    {
        if (Array_Of_Players[i].Money <= 0)
        {
            printf(" %s is dead ", Array_Of_Players[i].Name);
            Array_Of_Players[i].dead = 1;
            Index_Of_Dead_P = i;
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
                    break;
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
                    break;
                }
            }


        }
    }
    printf("On vient de break");
    for (int j=0; j<*Number_of_Players; j++)
        Display_Of_Players(Array_Of_Players,j);

    
    Player *New_Array = malloc(New_number_of_players * sizeof(Player));

    int j = 0;  // New index for the new array
    for (int i = 0; i < *Number_of_Players; i++)
    {
        if (i!= Index_Of_Dead_P)
        {
            New_Array[j] = Array_Of_Players[i];  // Copies only the remaining players
            j++;
        }
    }

    *Number_of_Players = New_number_of_players;

    printf("ON SORT DU VERYF");
    for (int j=0; j<*Number_of_Players; j++)
        Display_Of_Players(New_Array,j);

    printf("\n --------\n");
    return New_Array;
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


int Switch_Roles(Player *Array_Of_Players, int Number_Of_Players) {
    int Index_Dealer = -1, Index_SB = -1, Index_BB = -1;
    
    
    for (int i = 0; i < Number_Of_Players; i++) {
        if (strcmp(Array_Of_Players[i].Role, "Dealer") == 0) {
            Index_Dealer = i;
        } else if (strcmp(Array_Of_Players[i].Role, "Small Blind") == 0) {
            Index_SB = i;
        } else if (strcmp(Array_Of_Players[i].Role, "Big Blind") == 0) {
            Index_BB = i;
        }
    }
    
    
    for (int i = 0; i < Number_Of_Players; i++) {
        strcpy(Array_Of_Players[i].Role, "Neutre");
    }

   
    if (Index_Dealer != -1) {
        strcpy(Array_Of_Players[(Index_Dealer + 1) % Number_Of_Players].Role, "Dealer");
    }
    if (Index_SB != -1) {
        strcpy(Array_Of_Players[(Index_SB + 1) % Number_Of_Players].Role, "Small Blind");
    }
    if (Index_BB != -1) {
        strcpy(Array_Of_Players[(Index_BB + 1) % Number_Of_Players].Role, "Big Blind");
    }

    // Retourner l'index du nouveau Dealer
    return (Index_Dealer + 1) % Number_Of_Players;
}

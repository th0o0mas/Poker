#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PLAYERS 14
#define ROLE_SIZE 11
#define NAME_SIZE 20
#define STATUS_SIZE 7

// Define the Player structure
typedef struct Player {
    char role[ROLE_SIZE];   // Player's role (Dealer, Small Blind, etc.)
    char name[NAME_SIZE];   // Player's name
    char status[STATUS_SIZE]; // Player's status (All-in, Fold, Raise, etc.)
    int money;              // Player's money
    int bet;                // Player's current bet
} Player;

// Function to display player information
void DisplayPlayerInfo(Player *players, int index) {
    printf("Money: %d, Name: %s", players[index].money, players[index].name);
}

// Function to add a new player
void AddPlayer(char *name, int money, char *role, char *status, Player *new_player) {
    // Copy the player's name, role, and status into the new player struct
    strcpy(new_player->name, name);
    strcpy(new_player->role, role);
    strcpy(new_player->status, status);

    // Initialize player's money and bet
    new_player->money = money;
    new_player->bet = 0;
}

// Function to register players
void RegisterPlayers(Player *player_array, int *current_player_count) {
    char name[NAME_SIZE];
    char role[ROLE_SIZE] = "Neutral";
    char status[STATUS_SIZE] = "Neutral";
    int money = 2000;
    int player_index = *current_player_count;

    while (player_index < 5) { // For simplicity, limit to 5 players
        printf("Please enter the name of player %d: ", player_index);
        
        if (fgets(name, NAME_SIZE, stdin) != NULL && *name != '.') {
            AddPlayer(name, money, role, status, &player_array[player_index]);
            DisplayPlayerInfo(player_array, player_index);
            player_index++;
        } else {
            fprintf(stderr, "Error reading input or end of acquisition\n");
            break;
        }
    }

    // Update the current player count
    *current_player_count = player_index;
}

// Function to initialize player roles
void InitializeRoles(Player *players) {
    // Simple role assignment: 0 = Dealer, 1 = Small Blind, 2 = Big Blind
    strcpy(players[0].role, "Dealer");
    strcpy(players[1].role, "Small Blind");
    strcpy(players[2].role, "Big Blind");
}

// Function to add money to a player
void AddMoney(Player *player, int amount) {
    player->money += amount;
}

// Function to display available actions
void ShowPlayerOptions() {
    printf("\nPossible actions:\n");
    printf("1. Raise\n");
    printf("2. Call\n");
    printf("3. Fold\n");
    printf("4. All-In\n");
    printf("Choose your action (1, 2, 3, or 4): ");
}

int main() {
    int player_count = 0;  // Initialize player count
    Player player_array[MAX_PLAYERS];  // Array to hold players

    // Register players
    RegisterPlayers(player_array, &player_count);

    // Initialize player roles
    InitializeRoles(player_array);

    // More game logic can be added here...

    return 0;
}

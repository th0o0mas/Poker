#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Def Structures

typedef struct Player Player;
struct Player
{
    char *Role; 
    char *Nom;
    int Argent;
    int Mise;
};
//

void Affichage_Joueur(Player Joueur)
{
    /* Montre uniquement Argent */
    printf(" \n Nom : %s, Argent : %d, Role : %s \n ", Joueur.Nom, Joueur.Argent, Joueur.Role);
}

Player Ajouter_Joueur(char *Name, int Argent, char *Role_g)
{
    /* Création d'un joueur */
    Player *Player_cree = malloc(sizeof(*Player_cree));
    if (Player_cree == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    /* Allocation mémoire pour le nom et copie du nom */
    Player_cree->Nom = malloc(strlen(Name) + 1); /*Caractère arrêt du string d'où le +1*/
    if (Player_cree->Nom == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le nom\n");
        exit(EXIT_FAILURE);
    }
    strcpy(Player_cree->Nom, Name);/*Nous permet de copier Name dans Player_cree*/

    Player_cree->Role = malloc(strlen(Role_g) + 1); /*Caractère arrêt du string d'où le +1*/
    if (Player_cree->Role == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le nom\n");
        exit(EXIT_FAILURE);
    }
    strcpy(Player_cree->Role, Role_g);

    /* Modifications attributs */
    Player_cree->Argent = Argent;
    Player_cree->Mise = 0;

    return *Player_cree;
}

int Enregistrement_des_Joueurs(Player Record[6])
{
    int Joueurs_presents = 1;
    char Nom[20];
    scanf("%s", Nom);
    char Role[20] = "Neutre";
    int Argent = 2000;
    Player Joueur = Ajouter_Joueur(Nom, Argent, Role);
    Record[0] = Joueur;

    /* Boucle pour ajouter des joueurs */
    while (Joueurs_presents < 6 && *Nom != '7')  // Utilise && pour une condition d'arrêt correcte
    {
        
        
        scanf("%s", Nom);
        if (*Nom != '7')
        {
            Joueurs_presents++;
            Joueur = Ajouter_Joueur(Nom, Argent, Role);
            Record[Joueurs_presents - 1] = Joueur;
        }
        else
        {
            printf("Caractère sortie fourni \n");
            break;
        }
        
    }
    return Joueurs_presents;

}



int main()
{
    int Joueurs_nombre;
    Player Record[6];
    Joueurs_nombre= Enregistrement_des_Joueurs(Record);
    
    for (int i = 0; i < Joueurs_nombre; i++) {
        Affichage_Joueur(Record[i]);
    }
    
    
    /*------------------------------------------*/
    
    for (int i = 0; i < Joueurs_nombre; i++) {
        free(Record[i].Nom);
        free(Record[i].Role);  // Libérer de chaque élement allouer dynamiquement ( à ajouter en fin de processus)
    }


    /*-----------------------------------------*/

    return 0;
}

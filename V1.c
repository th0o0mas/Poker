#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

// Def Structures

typedef struct Player Player;
struct Player
{
    int Role; /* 1 = Dealer, 2= SB, 3=BB */
    char *Nom;
    int Argent;
    int Mise;
};

typedef struct Viseur Viseur;
struct Viseur
{
    Player *Ptr_Player;
};

//



void Affichage_Joueur(Player *Joueur)
{
    if (Joueur = NULL)
    {
        printf("Mauvais pointeur fourni");
    }
    else
    {
        printf("Ici");
        /*Montre uniquement Argent*/
        printf("Nom %d",Joueur->Argent);
    }
}


Player Ajouter_Joueur(char *Name, int Argent, int Role)
{
    
    /* Création d'un joueur*/
    
    Player *Player_cree = malloc(sizeof(*Player_cree));
    if (Player_cree == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    /*-----------------------*/

    /* Modifications attributs*/
    
    Player_cree->Argent=Argent;
    Player_cree->Nom=*Name;
    Player_cree->Role=Role;
    /*Non défini encore donc on le met à 0*/
    Player_cree->Mise=0;

    /*------------------------*/

    /* On va return l'adresse de notre Joueur ( en temps que constante afin d'être sûr de ne pas l'altérer)*/
    Affichage_Joueur(Player_cree);
    return *Player_cree;
    /*Soucis car retourne adresse d'une variable locale mais je voudrais que cette var soit globale et ensuite la stocker dans un viseur*/

}




int main()
{
    char Nom[20]="Thomas";
    int Argent=2000;
    int Role = 0;
    Player Joueur;
    printf("0");
    Joueur = Ajouter_Joueur(Nom,Argent,Role);
    printf("B");
    return 0;


}
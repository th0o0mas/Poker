#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

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

    /*Montre uniquement Argent*/
    printf("Nom : %s, Argent : %d, Role : %s ",Joueur.Nom,Joueur.Argent,Joueur.Role);
    /* Mises non défnie pour l'instant*/
    
}


Player Ajouter_Joueur(char *Name, int Argent, char *Role)
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
    Player_cree->Nom=Name;
    Player_cree->Role=Role;
    /*Non défini encore donc on le met à 0*/
    Player_cree->Mise=0;

    /*------------------------*/

    /* On va return l'adresse de notre Joueur ( en temps que constante afin d'être sûr de ne pas l'altérer)*/
    return *Player_cree;
    /*Soucis car retourne adresse d'une variable locale mais je voudrais que cette var soit globale et ensuite la stocker dans un viseur*/

}




int main()
{
    int Joueurs_presents = 1;
    Player Record[6];

    /* Définition du premier joueur*/
    Player Joueur;
    char Nom[20];
    scanf("%s", &Nom);
    char Role[20]="Neutre";
    int Argent =2000;
    Joueur = Ajouter_Joueur(Nom,Argent,Role);
    Record[0]=Joueur;
    /*------------------------------*/

    while (Joueurs_presents <5 || *Nom !='=' ) /* Condition d'arrêt est lorsque l'on rentre = uniquement*/
    {
        Joueurs_presents++;
        char name[20];
        scanf("%s", &name);
        /* Conditions pas touchées encore mais faisable*/
        char Role[20]="Neutre";
        int Argent =2000;
        /*-----------------------------------------------*/
        if (*name !='=')
        {
            Player Joueur;
            Joueur = Ajouter_Joueur(name,Argent,Role);
            Record[Joueurs_presents-1]=Joueur; /* -& car indices commencent à 0 et notre Joueur présent lui à 1*/

        }
        else
        {
            printf("Caractère exception fourni");
            break;
        }
        
    }
    Affichage_Joueur(Record[0]);
    Affichage_Joueur(Record[1]);
    return 0;


}
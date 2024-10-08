#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Def Structures

typedef struct Player Player;
struct Player
{
    char *Role; 
    char *Nom;
    char *Etat; /*Nous permet d'y enregistrer si ALL IN, si se couche et si suit ou raise ou Mort*/
    int Argent;
    int Mise;
};
//

void Affichage_Joueur(Player Joueur)
{
    /* Montre uniquement Argent */
    printf(" \n Nom : %s, Argent : %d, Role : %s \n ", Joueur.Nom, Joueur.Argent, Joueur.Role);
}

Player Ajouter_Joueur(char *Name, int Argent, char *Role_g, char *Etat_g)
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

    Player_cree->Role = (char*) malloc(11); /*On prend 11 carac pour enregistrer small blind*/
    if (Player_cree->Role == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le nom\n");
        exit(EXIT_FAILURE);
    }
    strcpy(Player_cree->Role, Role_g);

    Player_cree->Etat = (char*) malloc(7); /*7 pour ALL IN et moins pour les autres*/
    if (Player_cree->Etat == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le nom\n");
        exit(EXIT_FAILURE);
    }
    strcpy(Player_cree->Etat, Etat_g);

    /* Modifications attributs */
    Player_cree->Argent = Argent;
    Player_cree->Mise = 0;

    return *Player_cree;
}

int Enregistrement_des_Joueurs(Player Record[6])
{
    int Joueurs_presents = 1;
    char Nom[20];
    scanf("%s\n", Nom);
    char Role[20] = "Neutre";
    char Etat[8] ="Neutre";
    int Argent = 2000;
    Player Joueur = Ajouter_Joueur(Nom, Argent, Role,Etat);
    Record[0] = Joueur;

    /* Boucle pour ajouter des joueurs */
    while (Joueurs_presents < 6 && *Nom != '7')  // Utilise && pour une condition d'arrêt correcte
    {
        
        scanf("%s\n", Nom);
        if (*Nom != '7')
        {
            Joueurs_presents++;
            Joueur = Ajouter_Joueur(Nom, Argent, Role,Etat);
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


void Initialisation_Roles(Player Record[6])
{
    /* On initialise les rôles de manière assez bête , 0 prend Dealer, 1 Prend SB, 2 BB*/
    Record[0].Role="Dealer";
    Record[1].Role="Small Blind";
    Record[2].Role="Big Blind";
}



int Affichage_Argent_Pot(Player Record[6], int Joueurs_nombre)
{
    int Somme;
    for (int i = 0; i < Joueurs_nombre; i++) {
        Somme+=Record[i].Mise;
    }
    return Somme;
}

void Ajouter_Argent(Player Joueurs, int Argent_incremente)
{
    Joueurs.Argent += Argent_incremente;
}

void Mise(Player Record[6], int Joueurs_nombre, int Small_Blind_Actuelle)
{
    /* On commence d'abord par mettre les mises de petite blinde et grosse blinde (en s'assurant qu'ils aient assez, sinon ils sont all in et sinon)*/
    for (int i=0; i<Joueurs_nombre; i++)
    {
        if (Record[i].Role=="Small Blind" && Record[i].Etat!="Mort") 
        {
            if (Record[i].Argent > Small_Blind_Actuelle)
            {    
                Record[i].Mise=Small_Blind_Actuelle;
                Ajouter_Argent(Record[i],-Small_Blind_Actuelle);
            }
            else
            {
                Record[i].Role="All In";
                Record[i].Mise=Record[i].Argent;
                Ajouter_Argent(Record[i],-Record[i].Argent);
            }
        }
        if (Record[i].Role=="Big Blind" && Record[i].Etat!="Mort") 
        {
            if (Record[i].Argent > 2* Small_Blind_Actuelle)
            {    
                Record[i].Mise=Small_Blind_Actuelle;
                Ajouter_Argent(Record[i],-Small_Blind_Actuelle);
            }
            else
            {
                Record[i].Role="All In";
                Record[i].Mise=Record[i].Argent;
                Ajouter_Argent(Record[i],-Record[i].Argent);
            }
        }
    }


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
    Initialisation_Roles(Record);
    /*Marche bien */

    
    for (int i = 0; i < Joueurs_nombre; i++) {
        free(Record[i].Nom);
        free(Record[i].Role);
        free(Record[i].Etat);  // Libérer de chaque élement allouer dynamiquement ( à ajouter en fin de processus)
    }


    /*-----------------------------------------*/

    return 0;
}

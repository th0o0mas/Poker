#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
// Je vais définir les liste chaînées au cas ou

typedef struct Player Player;
struct Player
{
    int Argent;
    char *Nom;
    int Role; /* Dealer = 0, Small Blind = 1, Big Blind =2*/
    /*Username *suivant;*/ /* Ajoutable si on veut passer en liste Chainée*/
};

typedef struct Liste Liste;
struct Liste
{
    Player *Premier_P;
};

// Aucune idée si ça marche, on verra

Liste Ajouter_Joueur_Avec_Return_Adresse(char nom[],int argent, int role){


    Liste *Debut_Chaine = malloc(sizeof(*Debut_Chaine));
    if (Debut_Chaine == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    Player *User_1 = malloc(sizeof(*User_1));
    if (User_1 == NULL) {
        printf("Erreur d'allocation mémoire\n");
        free(Debut_Chaine);  // Libérer la mémoire allouée précédemment
        exit(EXIT_FAILURE);
    }
    /* Argent *Money_1 = malloc(sizeof(*Money_1));*/
    /*On définir un élement de Username*/
    /*Money_1->Monnaie=10;*/
    User_1->Nom = nom;
    User_1->Role = role;
    User_1->Argent = argent;
    Debut_Chaine ->Premier_P = User_1;
    return *Debut_Chaine;
}

/* On a pas d'insertion car uniquement 2 cases*/

void Affichage_De_La_Case_Pointee(Liste *Liste)
{
    char role;
    /* Overkill, on prend la structure classique pour une liste chainée même si que deux élements mais bon*/
    if (Liste == NULL)
    {
        printf("Liste ne pointe nulle part");
    }
    if (Liste->Premier_P->Role == 0){
        role='D';
    }
    else if (Liste->Premier_P->Role ==1)
    {
        role='S';
    }
    else if (Liste->Premier_P->Role ==2)
    {
        role='B';
    }
    else
    {
        role= 'n';
    }
    
    
    printf(" %s : $%d  role : %c \n", Liste->Premier_P->Nom, Liste->Premier_P->Argent, role);
    
}

void Ajouter_Argent(Liste *Adresse_du_gagnant_ou_perdant, int Number_to_Add)
{
    if (Adresse_du_gagnant_ou_perdant == NULL)
    {
        printf("La liste n'a pas été initialisée");
        exit(EXIT_FAILURE);
    }
    Adresse_du_gagnant_ou_perdant->Premier_P->Argent += Number_to_Add;

}

void Rotation_Role(Liste *Record_Of_Players[], int Nombre_Joueurs)
{
   int index_deal;
   for (int i=0; i<Nombre_Joueurs;i++)
   {
    if (Record_Of_Players[i]->Premier_P->Role = 0)/*Si c'est le dealer*/
    {
        index_deal =i;
        break;
    }
   }

   
/* Tout n'est pas traité mais idée okay*/
}    

int main() {

    int *Pointeur;
    int a=10;
    Pointeur = &a;
    printf("%d", *Pointeur);
    /* Partie en amont du jeu pour définir les joueurs*/
    Liste *Record_Of_Players[6];
    Liste Case_de_lancement;
    int Nombre_joueurs;
    for (int i =0; i<5; i++)
    {
        char name[20];
        scanf("%s", &name);
        if (*name !='=')
        {
            
            Case_de_lancement = Ajouter_Joueur_Avec_Return_Adresse(name, 2000,-1);
            Nombre_joueurs++;
            Record_Of_Players[i] = &Case_de_lancement; /* Toutes nos adresses sont enregistrées ( possible mysql)*/
            Affichage_De_La_Case_Pointee(&Case_de_lancement);/* Le &Case... est notre pointeur vers le début de notre élement*/
        }
        else
        {
            printf("Caractère stop acqui \n");
            break;
        }
    }   

    /* Fin Partie def avec adresses stockées dans Record*/
    /* Partie Rotation et ou initialisation rôles*/
    /* On commence par balayer notre record pour voir si au moins une valeure diff de 0 en rôle est présente, sinon on les ajoutes*/
    
    /* Création des rôles*/
    Record_Of_Players[0]->Premier_P->Role =0;
    Record_Of_Players[1]->Premier_P->Role =1;
    Record_Of_Players[2]->Premier_P->Role =2;
    /*--------*/
    /* Initialisation sûre des rôles*/
    printf("\n \n");
    Affichage_De_La_Case_Pointee(Record_Of_Players[0]);
    printf("\n en dessous indice 1 \n");
    Affichage_De_La_Case_Pointee(Record_Of_Players[1]);

    Sleep(4000);
    return 0;
}

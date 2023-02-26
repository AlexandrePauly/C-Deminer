 /*!
\file fonctions.c
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 14 décembre 2022
\brief Démineur
*/

//Inclusion des en-têtes de librairie
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "fonctions.h"

/*!
\def ERREUR_SAISIE Code d'erreur associé à la saisie
\def ERREUR_allocation Code d'erreur associé à l'allocation
*/

#define ERREUR_SAISIE -1
#define ERREUR_ALLOCATION -1

struct Demineur;
struct Plateau;

/*!
\fn int SaisieEntier()
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 14 décembre 2022
\brief Vérification de saisie
\return int_nb si tout s'est bien passé
*/

int SaisieEntier()
{
	int int_nb; //Variable demandée à l'utilisateur
	int int_retour; //Variable de retour
	
	//Lecture de l'entrée
	int_retour = scanf("%d", &int_nb);
	
	//Vérification de l'entrée
	if (int_retour == 0)
	{
		printf("Vous n'avez pas saisi un entier.\n");
		exit(ERREUR_SAISIE);
	}
	
	//Retourne int_nb quand tout s'est bien passé
	return (int_nb);
}

/*!
\fn void intVerifAllocation(int* pointeur)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 2 janvier 2023
\brief Vérification de l'allocation de mémoire
\param pointeur = Pointeur d'entier
*/

void intVerifAllocation(int* pointeur)
{
	//Si l'allocation a échouée, affichage d'un message et arrêt du programme
	if(pointeur == NULL)
	{
		printf("L'allocation a échouée.\n");
		exit(ERREUR_ALLOCATION);
	}
}

/*!
\fn void structVerifAllocation(struct Plateau* pointeur)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 15 janvier 2023
\brief Vérification de l'allocation de mémoire 
\param pointeur = Pointeur d'entier
*/

void structVerifAllocation(struct Plateau* pointeur)
{
	//Si l'allocation a échouée, affichage d'un message et arrêt du programme
	if(pointeur == NULL)
	{
		printf("L'allocation a échouée.\n");
		exit(ERREUR_ALLOCATION);
	}
}

/*!
\fn struct Plateau* creerPlateau(int int_dimensions, int int_nbMinesRestantes)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 15 janvier 2023
\brief Création du plateau de jeu
\param int_dimensions = Dimensions du plateau
\param int_nbMinesRestantes = Nombre de mines
\return sPlateau quand tout s'est bien passé
*/

struct Plateau* creerPlateau(int int_dimensions, int int_nbMinesRestantes)
{
    struct Plateau* sPlateau; //Plateau de jeu
    int i; //Variable de boucle

    //Réservation de l'espace mémoire et appel de fonction
    sPlateau = malloc(sizeof(struct Plateau));
    structVerifAllocation(sPlateau);

    //Initialisation de variables
    sPlateau->taillePlateau = int_dimensions;
    sPlateau->nbMines = int_nbMinesRestantes;

    //Réservation de l'espace mémoire
    sPlateau->pttDem_plateau = malloc(sPlateau->taillePlateau * sizeof(struct Demineur*));
    for (i=0 ; i<sPlateau->taillePlateau ; i++) 
    {
        sPlateau->pttDem_plateau[i] = malloc(sPlateau->taillePlateau * sizeof(struct Demineur));
        
        //Si l'allocation a échouée, affichage d'un message et arrêt du programme
        if(sPlateau->pttDem_plateau[i] == NULL)
        {
            printf("L'allocation a échouée.\n");
            exit(ERREUR_ALLOCATION);
        }
    }

    //Retourne sPlateau si tout s'est bien passé
    return (sPlateau);
}

/*!
\fn void initGrille(struct Plateau* pstruct_plateau)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 2 janvier 2023
\brief Initialisation du plateau de jeu
\param pstruct_plateau = Plateau de jeu
*/

void initGrille(struct Plateau* pstruct_plateau)
{
    int i; //Lignes du plateau de jeu
    int j; //Colonnes du plateau de jeu
    
    //Initialisation de la grille
    for(i=0 ; i<pstruct_plateau->taillePlateau ; i++)
    {
        for(j=0 ; j<pstruct_plateau->taillePlateau ; j++)
        {
            //On considère toute les cases comme vide en début de jeu
            pstruct_plateau->pttDem_plateau[i][j].mine = 0;
            pstruct_plateau->pttDem_plateau[i][j].case_vide = 1;
            pstruct_plateau->pttDem_plateau[i][j].drapeau = 0;
            pstruct_plateau->pttDem_plateau[i][j].nbMinesVoisines = 0;
            pstruct_plateau->pttDem_plateau[i][j].case_decouverte = 0;
        }
    }
}

/*!
\fn void MinesVoisines(struct Plateau* pstruct_plateau)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 2 janvier 2023
\brief Placement des cases voisines d'une mine
\param pstruct_plateau = Plateau de jeu
*/

void MinesVoisines(struct Plateau* pstruct_plateau)
{
    int i; //Lignes du plateau de jeu
    int j; //Colonnes du plateau de jeu
    int k; //Variable de boucle
    int l; //Variable de boucle

    //Incrémentation des cases voisines d'une mine
    for (i=0 ; i<pstruct_plateau->taillePlateau ; i++) 
    {
        for (j=0 ; j<pstruct_plateau->taillePlateau ; j++) 
        {
            //Parcourir les cellules voisines
            for (k=-1 ; k<=1 ; k++) 
            {
                for (l=-1 ; l<=1 ; l++) 
                {
                    //Si la cellule voisine est dans la grille
                    if (i+k >= 0 && i+k < pstruct_plateau->taillePlateau && j+l >= 0 && j+l < pstruct_plateau->taillePlateau) 
                    {
                        //Si la cellule voisine est une mine
                        if (pstruct_plateau->pttDem_plateau[i+k][j+l].mine == 1) 
                        {
                            pstruct_plateau->pttDem_plateau[i][j].nbMinesVoisines++;
                        }
                    }
                }
            }
        }
    }
}

/*!
\fn void afficherGrille(struct Plateau* pstruct_plateau)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 2 janvier 2023
\brief Affichage du plateau de jeu
\param pstruct_plateau = Plateau de jeu
*/

void afficherGrille(struct Plateau* pstruct_plateau)
{
    int i; //Lignes du plateau de jeu
    int j; //Colonnes du plateau de jeu
    int k; //Variable de boucle
    int int_ligne; //Valeur de la colonne
    int int_colonne; //Valeur de la colonne

    //Initialisation de variable
    int_ligne = 0;
    int_colonne = 0;

    //Si le plateau est de taille 10
    if(pstruct_plateau->taillePlateau == 10)
    {
        //Affichage de parties de la grille
        printf("\n   ");
        for(k=0 ; k<pstruct_plateau->taillePlateau ; k++)
        {
            printf(" %d  ", int_colonne++);
        }
        printf("\n  +");
        for(k=0 ; k<pstruct_plateau->taillePlateau ; k++)
        {
            printf("---+");
        }
        printf("\n");
    }
    //Sinon s'il est plus grand
    else if(pstruct_plateau->taillePlateau > 10)
    {
        //Affichage de parties de la grille
        printf("\n    ");
        for(k=0 ; k<pstruct_plateau->taillePlateau ; k++)
        {
            if(k<10)
            {
                printf(" %d  ", int_colonne++);
            }
            else
            {
                printf(" %d ", int_colonne++);
            }
        }
        printf("\n   +");
        for(k=0 ; k<pstruct_plateau->taillePlateau ; k++)
        {
            printf("---+");
        }
        printf("\n");
    }

    //Initialisation de la grille
    for(i=0 ; i<pstruct_plateau->taillePlateau ; i++)
    {
        //Si le plateau est de taille 10
        if(pstruct_plateau->taillePlateau == 10)
        {
            //Affichage de parties de la grille
            printf("%d ", int_ligne++);
        }
        //Sinon s'il est plus grand
        else if(pstruct_plateau->taillePlateau > 10)
        {
            //Si la ligne est inférieure à 10
            if(int_ligne < 10)
            {
                //Affichage de parties de la grille
                printf("%d  ", int_ligne++);
            }
            //Sinon
            else
            {
                //Affichage de parties de la grille
                printf("%d ", int_ligne++);
            }
        }

        for(j=0 ; j<pstruct_plateau->taillePlateau ; j++)
        {
            //Affichage de parties de la grille
            printf("|");

            //Si la case a été découverte
            if (pstruct_plateau->pttDem_plateau[i][j].case_decouverte == 1 && pstruct_plateau->pttDem_plateau[i][j].mine == 0)
            {
                //Si c'est une case voisine d'une ou plusieurs mines
                if (pstruct_plateau->pttDem_plateau[i][j].nbMinesVoisines > 0 )
                {
                    printf(" %d ", pstruct_plateau->pttDem_plateau[i][j].nbMinesVoisines);
                }
                //Sinon si ce n'est pas une case voisine d'une mine
                else
                {   
                    //On affiche V pour vide pour avoir un repaire visuel

                    printf("   ");
                }
            }
            //Sinon si la case est un drapeau
            else if (pstruct_plateau->pttDem_plateau[i][j].drapeau == 1)
            {
                printf(" D ");
            }
            //Sinon si la case n'a pas été découverte
            else
            {
                printf("   ");
            }
        }

        //Si le plateau est de taille 10
        if(pstruct_plateau->taillePlateau == 10)
        {
            //Affichage de parties de la grille
            printf("|");
            printf("\n  +");
            for(k=0 ; k<pstruct_plateau->taillePlateau ; k++)
            {
                printf("---+");
            }           
        }
        //Sinon s'il est plus grand
        else if(pstruct_plateau->taillePlateau > 10)
        {
            //Affichage de parties de la grille
            printf("|");
            printf("\n   +");
            for(k=0 ; k<pstruct_plateau->taillePlateau ; k++)
            {
                printf("---+");
            }
        }
        printf("\n");
    }
	
    /*Ceci est une grille à afficher pour faciliter le test du jeu, elle en affiche une deuxième avec la position des mines et des cases voisines */
    /*
    //Initialisation de variable
    int_ligne = 0;
    int_colonne = 0;

    //Si le plateau est de taille 10
    if(pstruct_plateau->taillePlateau == 10)
    {
        //Affichage de parties de la grille
        printf("\n   ");
        for(k=0 ; k<pstruct_plateau->taillePlateau ; k++)
        {
            printf(" %d  ", int_colonne++);
        }
        printf("\n  +");
        for(k=0 ; k<pstruct_plateau->taillePlateau ; k++)
        {
            printf("---+");
        }
        printf("\n");
    }
    //Sinon s'il est plus grand
    else if(pstruct_plateau->taillePlateau > 10)
    {
        //Affichage de parties de la grille
        printf("\n    ");
        for(k=0 ; k<pstruct_plateau->taillePlateau ; k++)
        {
            if(k<10)
            {
                printf(" %d  ", int_colonne++);
            }
            else
            {
                printf(" %d ", int_colonne++);
            }
        }
        printf("\n   +");
        for(k=0 ; k<pstruct_plateau->taillePlateau ; k++)
        {
            printf("---+");
        }
        printf("\n");
    }

    //Initialisation de la grille
    for(i=0 ; i<pstruct_plateau->taillePlateau ; i++)
    {
        //Si le plateau est de taille 10
        if(pstruct_plateau->taillePlateau == 10)
        {
            //Affichage de parties de la grille
            printf("%d ", int_ligne++);
        }
        //Sinon s'il est plus grand
        else if(pstruct_plateau->taillePlateau > 10)
        {
            //Si la ligne est inférieure à 10
            if(int_ligne < 10)
            {
                //Affichage de parties de la grille
                printf("%d  ", int_ligne++);
            }
            //Sinon
            else
            {
                //Affichage de parties de la grille
                printf("%d ", int_ligne++);
            }
        }

        for(j=0 ; j<pstruct_plateau->taillePlateau ; j++)
        {
            //Affichage de parties de la grille
            printf("|");

            //Si c'est une mine
            if (pstruct_plateau->pttDem_plateau[i][j].mine == 1)
            {
                printf(" * ");
            }
            else
            {
                //Si c'est une case voisine d'une ou plusieurs mines
                if (pstruct_plateau->pttDem_plateau[i][j].nbMinesVoisines > 0 )
                {
                    printf(" %d ", pstruct_plateau->pttDem_plateau[i][j].nbMinesVoisines);
                }
                else 
                {
                    //Si c'est une case vide
                    if (pstruct_plateau->pttDem_plateau[i][j].case_vide == 1 || pstruct_plateau->pttDem_plateau[i][j].case_decouverte == 1)
                    {
                        printf("   ");
                    }
                }
            }
        }

        //Si le plateau est de taille 10
        if(pstruct_plateau->taillePlateau == 10)
        {
            //Affichage de parties de la grille
            printf("|");
            printf("\n  +");
            for(k=0 ; k<pstruct_plateau->taillePlateau ; k++)
            {
                printf("---+");
            }           
        }
        //Sinon s'il est plus grand
        else if (pstruct_plateau->taillePlateau > 10)
        {
            //Affichage de parties de la grille
            printf("|");
            printf("\n   +");
            for(k=0 ; k<pstruct_plateau->taillePlateau ; k++)
            {
                printf("---+");
            }
        }
        printf("\n");
    }
    */
}

/*!
\fn void jeu(struct Plateau* pstruct_plateau, int int_nbMinesRestantes)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 2 janvier 2023
\brief Placement des mines
\param pstruct_plateau = Plateau de jeu
\param int_nbMinesRestantes = Nombre de mines initialisées
*/

void jeu(struct Plateau* pstruct_plateau, int int_nbMinesRestantes)
{
    int i; //Lignes du plateau de jeu
    int j; //Colonnes du plateau de jeu

    //Initialiser le générateur de nombres aléatoires
	srand(time(NULL));

    while(int_nbMinesRestantes > 0)
    {
        //Initialisation aléatoire de la position des mines
        i = rand()%pstruct_plateau->taillePlateau;
        j = rand()%pstruct_plateau->taillePlateau;

        //Vérification que la case n'ait pas déjà une mine
        if(pstruct_plateau->pttDem_plateau[i][j].mine == 0)
        {
            pstruct_plateau->pttDem_plateau[i][j].mine = 1;
            pstruct_plateau->pttDem_plateau[i][j].case_vide = 0;

            //Décrémentation du nombre de mines
            int_nbMinesRestantes--;
        }
    }

    //Appel de fonction pour placer les cases voisines d'une mine
    MinesVoisines(pstruct_plateau);
}

/*!
\fn int VerifVictoire(struct Plateau* pstruct_plateau)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 2 janvier 2023
\brief Vérifie si le joueuer a gagné
\param pstruct_plateau = Plateau de jeu
\return int_cpt quand tout s'est bien passé
*/

int VerifVictoire(struct Plateau* pstruct_plateau)
{
    int int_cpt; //Compteur
    int i; //Lignes du plateau de jeu
    int j; //Colonnes du plateau de jeu

    //Initialisation d'un compteur
    int_cpt = 0;
    
    //Itération du résultat
    for(i=0 ; i<pstruct_plateau->taillePlateau ; i++)
    {
        for(j=0 ; j<pstruct_plateau->taillePlateau ; j++)
        {
            if(pstruct_plateau->pttDem_plateau[i][j].case_decouverte == 1)
            {
                int_cpt++;
            }
        }
    }

    //Retourne int_cpt si tout s'est bien passé
    return(int_cpt);
}

/*!
\fn int VerifJeu(struct Plateau* pstruct_plateau i, int j, int int_nbMinesRestantes)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 2 janvier 2023
\brief Vérifie si la partie est terminée ou non
\param pstruct_plateau = Plateau de jeu
\param i = Lignes du plateau
\param j = Colonnes du plateau
\param int_nbMinesRestantes = Nombre de mines initialisées
\return un entier quand tout s'est bien passé
*/

int VerifJeu(struct Plateau* pstruct_plateau, int i, int j, int int_nbMinesRestantes)
{
    int int_cptVictoire; //Variable locale

    //Initialisation d'un compteur
    int_cptVictoire = VerifVictoire(pstruct_plateau);

    //Si le joueur a découvert toutes les cases, on retourne 2
    if (int_cptVictoire == pstruct_plateau->taillePlateau*pstruct_plateau->taillePlateau - int_nbMinesRestantes)
    {
        return(2);
    }
    else
    {
        //Si le joueur joue sur une mine, on retourne -1
        if (pstruct_plateau->pttDem_plateau[i][j].mine == 1)
        {
            return(1);
        }
        //Sinon si le joueur ne joue pas sur une mine
        else
        {
            return(0);
        }
    }
}

/*!
\fn void decouvrementCases(struct Plateau* pstruct_plateau, int N, int i, int j)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 2 janvier 2023
\brief Découvrement des cases
\param pttDemplateau = Plateau de jeu
\param N = Dimensions du plateau
\param i = Lignes du plateau
\param j = Colonnes du plateau
*/

void decouvrementCases(struct Plateau* pstruct_plateau, int N, int i, int j)
{    
    if(pstruct_plateau->pttDem_plateau[i][j].case_vide == 1 && pstruct_plateau->pttDem_plateau[i][j].nbMinesVoisines == 0)
    {
        //Initialisation de variables
        pstruct_plateau->pttDem_plateau[i][j].case_decouverte = 1;
        pstruct_plateau->pttDem_plateau[i][j].case_vide = 0;

        //Appel récursif en fonction de la case
        if (i == 0)
        {
            if (j == 0)
            {
                decouvrementCases(pstruct_plateau, N, i+1, j);
                decouvrementCases(pstruct_plateau, N, i+1, j+1);
                decouvrementCases(pstruct_plateau, N, i, j+1);
            }
            else if (j == N-1)
            {
                decouvrementCases(pstruct_plateau, N, i+1, j);
                decouvrementCases(pstruct_plateau, N, i+1, j-1);
                decouvrementCases(pstruct_plateau, N, i, j-1);
            }
            else
            {
                decouvrementCases(pstruct_plateau, N, i+1, j);
                decouvrementCases(pstruct_plateau, N, i+1, j+1);
                decouvrementCases(pstruct_plateau, N, i+1, j-1);
                decouvrementCases(pstruct_plateau, N, i, j+1);
                decouvrementCases(pstruct_plateau, N, i, j-1);
            }
        }
        else if (i == N-1)
        {
            if (j == 0)
            {
                decouvrementCases(pstruct_plateau, N, i-1, j);
                decouvrementCases(pstruct_plateau, N, i-1, j+1);
                decouvrementCases(pstruct_plateau, N, i, j+1);
            }
            else if (j == N-1)
            {
                decouvrementCases(pstruct_plateau, N, i-1, j);
                decouvrementCases(pstruct_plateau, N, i-1, j-1);
                decouvrementCases(pstruct_plateau, N, i, j-1);
            }
            else
            {
                decouvrementCases(pstruct_plateau, N, i-1, j);
                decouvrementCases(pstruct_plateau, N, i-1, j+1);
                decouvrementCases(pstruct_plateau, N, i-1, j-1);
                decouvrementCases(pstruct_plateau, N, i, j+1);
                decouvrementCases(pstruct_plateau, N, i, j-1);
            }
        }
        else
        {
            if (j == 0)
            {
                decouvrementCases(pstruct_plateau, N, i+1, j);
                decouvrementCases(pstruct_plateau, N, i+1, j+1);
                decouvrementCases(pstruct_plateau, N, i-1, j);
                decouvrementCases(pstruct_plateau, N, i-1, j+1);
                decouvrementCases(pstruct_plateau, N, i, j+1);
            }
            else if (j == N-1)
            {
                decouvrementCases(pstruct_plateau, N, i+1, j);
                decouvrementCases(pstruct_plateau, N, i+1, j-1);
                decouvrementCases(pstruct_plateau, N, i-1, j);
                decouvrementCases(pstruct_plateau, N, i-1, j-1);
                decouvrementCases(pstruct_plateau, N, i, j-1);
            }
            else
            {
                decouvrementCases(pstruct_plateau, N, i+1, j);
                decouvrementCases(pstruct_plateau, N, i+1, j+1);
                decouvrementCases(pstruct_plateau, N, i+1, j-1);
                decouvrementCases(pstruct_plateau, N, i-1, j);
                decouvrementCases(pstruct_plateau, N, i-1, j+1);
                decouvrementCases(pstruct_plateau, N, i-1, j-1);
                decouvrementCases(pstruct_plateau, N, i-1, j-1);
                decouvrementCases(pstruct_plateau, N, i, j+1);
                decouvrementCases(pstruct_plateau, N, i, j-1);
            }
        }
    }
    else
    {
        pstruct_plateau->pttDem_plateau[i][j].case_decouverte = 1;
    }
}

/*!
\fn void placementDrapeau(struct Plateau* pstruct_plateau)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 2 janvier 2023
\brief Placement des drapeaux
\param pstruct_plateau = Plateau de jeu
*/

void placementDrapeau(struct Plateau* pstruct_plateau)
{
    int i; //Lignes du plateau de jeu
    int j; //Colonnes du plateau de jeu

    //Demande et lecture de la case à jouer à l'utilisateur
    printf("\nQuelle ligne? ");
    i = SaisieEntier();

    //Vérification de l'entrée du joueur
    while (i < 0 && i > pstruct_plateau->taillePlateau)
    {
        printf("Quelle ligne? ");
        i = SaisieEntier();
    }

    //Demande et lecture de la case à jouer à l'utilisateurs
    printf("Quelle colonne? ");
    j = SaisieEntier();

    //Vérification de l'entrée du joueur
    while (j < 0 && j > pstruct_plateau->taillePlateau)
    {
        printf("Quelle colonne? ");
        j = SaisieEntier();
    }

    //Placement d'un drapeau
    if (pstruct_plateau->pttDem_plateau[i][j].case_decouverte == 0)
    {
        pstruct_plateau->pttDem_plateau[i][j].drapeau = 1;
        pstruct_plateau->pttDem_plateau[i][j].case_decouverte = 1;
    }
    //Sinon appel récursif jusqu'à que l'utilisateur sélectionne une case correcte
    else
    {
        placementDrapeau(pstruct_plateau);
    }
}

/*!
\fn void tourDeJeu(struct Plateau* pstruct_plateau, int* int_fin, int int_nbMinesRestantes)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 2 janvier 2023
\brief Tour de jeu
\param pstruct_plateau = Plateau de jeu
\param int_fin = Pointeur vers un entier (la valeur de l'entier renseigne sur les conditions de fin de partie)
\param int_nbMinesRestantes = Nombre de mines initialisées
*/

void tourDeJeu(struct Plateau* pstruct_plateau, int* int_fin, int int_nbMinesRestantes)
{
    int i; //Lignes du plateau de jeu
    int j; //Colonnes du plateau de jeu

    //Demande et lecture de la case à jouer à l'utilisateur
    printf("\nQuelle ligne? ");
    i = SaisieEntier();

    //Vérification de l'entrée du joueur
    while (i < 0 && i > pstruct_plateau->taillePlateau)
    {
        printf("Quelle ligne? ");
        i = SaisieEntier();
    }

    //Demande et lecture de la case à jouer à l'utilisateurs
    printf("Quelle colonne? ");
    j = SaisieEntier();

    //Vérification de l'entrée du joueur
    while (j < 0 && j > pstruct_plateau->taillePlateau)
    {
        printf("Quelle colonne? ");
        j = SaisieEntier();
    }

    //Affectation de variable
    pstruct_plateau->pttDem_plateau[i][j].case_decouverte = 1;

    //Appel de fonction
    *int_fin = VerifJeu(pstruct_plateau, i, j, int_nbMinesRestantes);
    decouvrementCases(pstruct_plateau, pstruct_plateau->taillePlateau, i, j);
}

/*!
\fn void Demineur(void)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 15 janvier 2023
\brief Jeu du démineur
*/

void Demineur(void)
{
    struct Plateau* pstruct_plateau; //Information sur le plateau de jeu
    int int_nbMinesRestantes; //Nombre de mines
    int int_dimensions; //Dimension du plateau
    int* int_fin; //Variable de fin de partie
    int int_action; //Action à réaliser
    int int_regles; //Règles du jeu
    int int_difficulte; //Niveau de difficulté

    //Demande et lecture d'un message
    printf("Avez-vous besoin d'un rappel des règles? (1 pour oui))\n");
    int_regles = SaisieEntier();

    if (int_regles == 1)
    {
        printf("\nLe but du jeu est de découvrir toutes les cases libres sans faire exploser les mines.\n");
        printf("Pour libérer une case, faire entrez les coordonnées de la case lorsque le moment est venu.\n");
        printf("Pour marquer une mine, entrez les coordonnées de la case lorsque le moment sera venu, ce qui fera apparaître un drapeau.\n");
        printf("Le chiffre qui s'affiche sur les cases indique le nombre de mines se trouvant à proximité : à gauche ou à droite, en haut ou en bas, ou en diagonale.\n");
        printf("Grâce aux indications données par les chiffres, vous pouvez libérer d'autres cases.\n");
        printf("Une fois le drapeau placé, vous pouvez deviner qu'il n'y a pas de mines aux endroits marqués.\n\n");
        sleep(10); //Permet d'attendre 10 secondes avant d'afficher la suite
    }

    //Demande et lecture d'un message
    printf("\nQuelle difficulté?\n");
    printf("1 - Débutant (10 mines)\n");
    printf("2 - Intermédiaire (40 mines)\n");
    printf("3 - Expert (99 mines)\n");
    int_difficulte = SaisieEntier();
    
    //Vérification de l'entrée du joueur
    while (int_difficulte > 3 && int_difficulte < 1)
    {
        //Demande et lecture d'un message
        printf("\nQuelle difficulté?\n");
        printf("1 - Débutant\n");
        printf("2 - Intermédiaire\n");
        printf("3 - Expert\n");
        int_difficulte = SaisieEntier();
    }

    //Si la difficulté est 1
    if(int_difficulte == 1)
    {
        //Initialisation de variables
        int_nbMinesRestantes = 10;
        int_dimensions = 10;
    }
    //Sinon si la difficulté est 2
    else if (int_difficulte == 2)
    {
        //Initialisation de variables
        int_nbMinesRestantes = 40;
        int_dimensions = 16;
    }
    //Sinon si la difficulté est 3
    else if (int_difficulte == 3)
    {
        //Initialisation de variables
        int_nbMinesRestantes = 99;
        int_dimensions = 22;
    }
    else
    {
        exit(-1);
    }

    //Réservation de l'espace mémoire et appel de fonction
    int_fin = (int*)malloc(sizeof(int));
    intVerifAllocation(int_fin);
    pstruct_plateau = creerPlateau(int_dimensions, int_nbMinesRestantes);
    structVerifAllocation(pstruct_plateau);

    //On réaffecte le nombre de mines car il est modifié dans le procédure jeu
    int_nbMinesRestantes = pstruct_plateau->nbMines;

    //Initialisation du plateau de jeu
    initGrille(pstruct_plateau);
    jeu(pstruct_plateau, int_nbMinesRestantes);
    afficherGrille(pstruct_plateau);

    //Initialisation de variables
    *int_fin = 0;

    //Jeu
    while (*int_fin == 0)
    {
        //On saute une ligne pour améliorer le visuel
        printf("\n");

        //Affichage du menu
        printf("Choisissez une action :\n");
        printf("1 - Révéler une cellule\n");
        printf("2 - Signaler une cellule\n");

        //Lecture de la réponse de l'utilisateur
        int_action = SaisieEntier();

        //Appel de fonction en fonction de l'action choisie
        if (int_action == 1)
        {
            tourDeJeu(pstruct_plateau, int_fin, int_nbMinesRestantes);
            printf("%d\n", *int_fin);
        }
        else if (int_action == 2)
        {
            placementDrapeau(pstruct_plateau);

            //On enlève une mine car le joueur a placé un drapeau
            int_nbMinesRestantes--;
        }

        //Affichage du plateau et de messages
        afficherGrille(pstruct_plateau);
        printf("\nMines : %d / %d", pstruct_plateau->nbMines - int_nbMinesRestantes, pstruct_plateau->nbMines);

    }

    //Si le joueur a perdu on affiche un message
    if(*int_fin == 1)
    {
        printf("\nBOOUUUUUMMMMMM !!!!!\n");
    }
    //Sinon, si le joueur a gagné on affiche un autre message
    else if(*int_fin == 2)
    {
        printf("\nFélicitations!\n");
    }

    //On saute une ligne pour améliorer le visuel
    printf("\n");

    //Libération de l'espace mémoire
    free(int_fin);
    free(pstruct_plateau);
    free(pstruct_plateau->pttDem_plateau);
}

/*!
\file fonctions.h
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 14 décembre 2022
\brief Démineur
*/

#ifndef __TP9_H_
#define __TP9_H_

struct Demineur
{
    int mine; //Variable des mines (1) ou non (0)
    int case_vide; //Variables des cases vide (1) ou non (0)
    int drapeau; //Variable des drapeaux (1) ou non (0)
    int nbMinesVoisines; //Variable du nombre de mines (s'incrémente s''il y en a au moins une)
    int case_decouverte; //Variable des cases découvertes (1) ou non (0)
};

struct Plateau
{
    int nbMines; //Nombre de mines sur le plateau
    int taillePlateau; //Nombre de lignes (resp colonnes) sur le plateau
    struct Demineur** pttDem_plateau; //Plateau de jeu
};

/*!
\fn int SaisieEntier()
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 12 décembre 2022
\brief Vérification de saisie
\return int_nb si tout s'est bien passé
*/

int SaisieEntier(void);

/*!
\fn void intVerifAllocation(int* pointeur)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 2 janvier 2023
\brief Vérification de l'allocation de mémoire
\param pointeur = Pointeur d'entier
*/

void intVerifAllocation(int* pointeur);

/*!
\fn void structVerifAllocation(struct Plateau* pointeur)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 15 janvier 2023
\brief Vérification de l'allocation de mémoire
\param pointeur = Pointeur d'entier
*/

void structVerifAllocation(struct Plateau* pointeur);

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

struct Plateau* creerPlateau(int int_dimensions, int int_nbMinesRestantes);

/*!
\fn void initGrille(struct Plateau* pstruct_plateau)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 2 janvier 2023
\brief Initialisation du plateau de jeu
\param pstruct_plateau = Plateau de jeu
*/

void initGrille(struct Plateau* pstruct_plateau);

/*!
\fn void MinesVoisines(struct Plateau* pstruct_plateau)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 2 janvier 2023
\brief Placement des cases voisines d'une mine
\param pstruct_plateau = Plateau de jeu
*/

void MinesVoisines(struct Plateau* pstruct_plateau);

/*!
\fn void afficherGrille(struct Plateau* pstruct_plateau)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 2 janvier 2023
\brief Affichage du plateau de jeu
\param pstruct_plateau = Plateau de jeu
*/

void afficherGrille(struct Plateau* pstruct_plateau);

/*!
\fn void jeu(struct Plateau* pstruct_plateau, int int_nbMinesRestantes)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 2 janvier 2023
\brief Placement des mines
\param pstruct_plateau = Plateau de jeu
\param int_nbMinesRestantes = Nombre de mines initialisées
*/

void jeu(struct Plateau* pstruct_plateau, int int_nbMinesRestantes);

/*!
\fn int VerifVictoire(struct Plateau* pstruct_plateau)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 2 janvier 2023
\brief Vérifie si le joueuer a gagné
\param pstruct_plateau = Plateau de jeu
\return int_cpt quand tout s'est bien passé
*/

int VerifVictoire(struct Plateau* pstruct_plateau);

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

int VerifJeu(struct Plateau* pstruct_plateau, int i, int j, int int_nbMinesRestantes);

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

void decouvrementCases(struct Plateau* pstruct_plateau, int N, int i, int j);

/*!
\fn void placementDrapeau(struct Plateau* pstruct_plateau)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 2 janvier 2023
\brief Placement des drapeaux
\param pstruct_plateau = Plateau de jeu
*/

void placementDrapeau(struct Plateau* pstruct_plateau);

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

void tourDeJeu(struct Plateau* pstruct_plateau, int* int_fin, int int_nbMinesRestantes);

/*!
\fn void Demineur(void)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 15 janvier 2023
\brief Jeu du démineur
*/

void Demineur(void);

#endif

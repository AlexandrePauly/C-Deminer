/*!
\file main.c
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 14 décembre 2022
\brief Démineur
*/

//Inclusion des en-têtes de librairie
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include "fonctions.h"

/*!
\fn int main(int argc, char** argv)
\author Alexandre Pauly <alexandre.pauly@cy-tech.fr>
\version 0.1 Premier jet
\date 14 décembre 2022
\brief Fonction principale
\param argc = nombre d'arguments en entrée
\param argv = valeur des arguments en entrée
\return 0 si tout s'est bien passé
*/

int main (int argc, char** argv)
{	
	Demineur();

	// Fin du programme, il se termine normalement, et donc retourne 0
	return (0);	
}

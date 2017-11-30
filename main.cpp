/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */


#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "Monster.h"
#include "Electric.h"
#include "Attack.h"
#include "Water.h"
#include "Rock.h"
#include "utils.h"
#include "terrain.h"
#include "Fire.h"
#include "Grass.h"
#include "Plant.h"
#include "Insect.h"
#include "time.h"
#include "Player.h"
#include "Object.h"
#include "Potion.h"
#include "Drug.h"
#include <vector>
#include <string>



int main()
{
	int nbMonstre = 0;

	// création des deux joueurs
	CPlayer Joueur1;
	CPlayer Joueur2;

	// initialise le terrain
	CTerrain monterrain;

	string nomFichierMonstre = "monster.txt";
	string nomFichierAttack = "attack.txt";
	string nomFichierObject = "object.txt";

	// choix du nombre de monstre par joueur
	printf("|*******************************************************************************************************************|\n");
	printf("|*******************************************************************************************************************|\n");
	printf("|**                                                                                                               **|\n");
	printf("|**   ***  ***     *****     ***  **   *******    *****   ******  ****  *******  ***  ***     *****     ***  **   **|\n");
	printf("|**   ** ** **   **     **   ***  **   **   **  **     *   ***   ***    **       ** ** **   **     **   ***  **   **|\n");
	printf("|**   ** ** **   **     **   ** ****   *******  **     *   ******       *******  ** ** **   **     **   ** ****   **|\n");
	printf("|**   **    **   **     **   **   **   **       **     *   ***   ***    **       **    **   **     **   **   **   **|\n");
	printf("|**   **    **     *****     **   **   **         *****   ******  ****  *******  **    **     *****     **   **   **|\n");
	printf("|**                                                                                                               **|\n");
	printf("|**                                                                        by: LEBBAT Badreddine                  **|\n");
	printf("|*******************************************************************************************************************|\n");
	printf("|*******************************************************************************************************************|\n");

	printf("\n\n Quel est le nombre de monstre par joueur ? : ");
	cin >> nbMonstre;
	
	// on initialise le tableau de monstres des joueurs 1 et 2
	Joueur1.setMonsterTab(createMonstre(1, nomFichierMonstre, nomFichierAttack, &monterrain, nbMonstre, nbAttack));
	Joueur2.setMonsterTab(createMonstre(2, nomFichierMonstre, nomFichierAttack, &monterrain, nbMonstre, nbAttack));

	// on attribue des objets aux joueurs
	Joueur1.setObjectTab(createTabObjet(nomFichierObject, nbObjet));
	Joueur2.setObjectTab(createTabObjet(nomFichierObject, nbObjet));

	// on commence la partie
	CommencerLeJeu(&Joueur1, &Joueur2, &monterrain);

	printf("\n\n\n");
	system("pause");
	system("pause");
	

	return EXIT_SUCCESS;
}










/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par Lebbat badreddine
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
#include <string>



/**************** jouer *****************
boucle de jeu
ARGV : CMonster *monster : monstre du joueur
	   int joueur : numéro du joueur
	   CMonster *ennemi : monstre de l'adversaire
retourne 0 si tout s'est bien passé
****************************************/

char jouer(CMonster *monster, CPlayer *JoueurCourant, int joueur, CMonster *ennemi, CPlayer *JoueurEnnemi, CTerrain *terrain_p)
{
	// va enregistrer le choix de l'utilisateur
	int choix = 0;

	// appel de la fonction gagner
	if (gagner(JoueurCourant->getMonsterTab(), joueur) == 0)
		return 0;

	// on affiche l'état des monstres s'ils ont changé
	if (ennemi->getEtat().paralysie == false)
	{
		monster->printMonstre();
		ennemi->printMonstre();
	}


	printf("\n\n\n\n\n\n=======================================");
	switch (joueur)
	{
		// joueur 1
		case 1:
			printf("\n==========> %s jouez : <==========\n", monster->getName().c_str());
			choix = monster->activite(ennemi, terrain_p);

			// si notre monstre est mort
			if (monster->getPoinVie() <= 0)
			{
				printf("\n\n\n %s mort, vous devez changer de monstre...", monster->getName().c_str());
				// on change de monstre et on joue
				monster = choixMonstre(1, JoueurCourant->getMonsterTab());
				monster->activite(ennemi, terrain_p);
			}

			// si on a choisit de changer de monstre
			else if (choix==555)
			{
				printf("\n\n\n Vous avez choisit de changer de monstre !");
				// on change de monstre et on joue
				monster = choixMonstre(1, JoueurCourant->getMonsterTab());
				monster->activite(ennemi, terrain_p);
			}

			// si on a choisit d'utiliser un objet
			else if (choix == 555)
			{
				cout << "\nVous avez choisi d'utiliser un objet !" << endl;
				JoueurCourant->printObject();

				// indice de l'objet dans le tableau d'objet
				cin >> choix;
				if ((unsigned)choix >= JoueurCourant->getObjectTab().size())
				{
					printf("\n Erreur ! Tapez un numero d'objet correct : ");
					cin >> choix;
				}
				JoueurCourant->useObject(choix, terrain_p, monster);
			}

			jouer(ennemi, JoueurEnnemi, 2, monster, JoueurCourant, terrain_p);
			break;

		// joueur 2
		case 2:
			printf("\n==========> %s jouez : <==========\n", monster->getName().c_str());
			choix = monster->activite(ennemi, terrain_p);

			// si notre monstre est mort
			if (monster->getPoinVie() <= 0)
			{
				printf("\n\n\n %s mort, vous devez changer de monstre...", monster->getName().c_str());
				// on change de monstre et on joue
				monster = choixMonstre(2, JoueurCourant->getMonsterTab());
				monster->activite(ennemi, terrain_p);
			}

			// si on a choisit de changer de monstre
			else if (choix == 555)
			{
				printf("\n\n\n Vous avez choisit de changer de monstre !");
				// on change de monstre et on joue
				monster = choixMonstre(2, JoueurCourant->getMonsterTab());
				monster->activite(ennemi, terrain_p);
			}

			// si on a choisit d'utiliser un objet
			else if (choix == 555)
			{
				cout << "\nVous avez choisi d'utiliser un objet !" << endl;
				JoueurCourant->printObject();

				// indice de l'objet dans le tableau d'objet
				cin >> choix;
				if ((unsigned)choix >= JoueurCourant->getObjectTab().size())
				{
					printf("\n Erreur ! Tapez un numero d'objet correct : ");
					cin >> choix;
				}
				JoueurCourant->useObject(choix, terrain_p, monster);
			}

			jouer(ennemi, JoueurEnnemi, 1, monster, JoueurCourant, terrain_p);
			break;
	}

	return 0;
}

/**************** gagner *****************
affiche le gagnant de la partie
ARGV : vector<CMonster *> Tabmonstres : monstre du joueur
int joueur : numéro du joueur
retourne 0 s'il y a un gagnant
1 si la partie continue
****************************************/
int gagner(vector<CMonster *> Tabmonstres, int joueur)
{
	unsigned int i = 0;
	int cpt = 0;			// compte le nombre de monstre en vie

	// parcourt du tableau
	for (i = 0; i < Tabmonstres.size(); i++)
	{
		// si le monstre est en vie 
		if (Tabmonstres[i]->getPoinVie()>0)
		{
			// compte le nombre de monstre en vie du joueur
			cpt++;
		}
	}

	// si le joueur actuel a perdu 
	if (cpt == 0)
	{	
		// le joueur 2 a gagné
		if (joueur == 1)
		{
			printf("\n\n********************************************************\n");
			printf("\n********************************************************\n");
			printf("************** Victoire du joueur 2 !!!!\n");
			printf("********************************************************\n");
			printf("********************************************************\n");
		}

		// le joueur 1 a gagné
		else
		{
			printf("\n\n********************************************************\n");
			printf("\n********************************************************\n");
			printf("************** Victoire du joueur 1 !!!!\n");
			printf("********************************************************\n");
			printf("********************************************************\n");
		}
	}
	return cpt;
}




// affiche le fichier dont le chemin est en paramètre
void affichageFichier(string const nomFichier)
{
	// ouverture en mode lecture
	ifstream fichier(nomFichier.c_str());

	if (fichier)
	{
		cout << "Liste des personnages disponibles :\n" << endl;

		string ligne; //Une variable pour stocker les lignes lues
		int i = 0;

		while (getline(fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
		{
			cout << ligne << endl;
		}

		fichier.close();
	}
	else
	{
		cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
	}

}




// Calcule nombre aléatoire flottant entre a et b
float frand_a_b(float a, float b)
{
	return (rand() / (float)RAND_MAX) * (b - a) + a;
}

// fonction lecture et création de monstre propre à chaque type
CElectric* lecture_Elec(ifstream *fichier, string nomMonstre)
{
	CElectric *monElec = NULL;

	unsigned int t = (unsigned int)time(NULL);		// va nous servir pour calculer des valeurs aléatoires
	srand(t);

	float HP[2];
	float speed[2];
	float Attack[2];
	float Defense[2];
	float Paralysis;
	float Wake;

	string tmp;			// va contenir les mots du fichier

	*fichier >> HP[0];
	*fichier >> HP[1];
	cout << HP[0] << " " << HP[1] << endl;

	*fichier >> tmp;
	cout << tmp << endl;
	*fichier >> speed[0];
	*fichier >> speed[1];
	cout << speed[0] << " " << speed[1] << endl;

	*fichier >> tmp;
	cout << tmp << endl;
	*fichier >> Attack[0];
	*fichier >> Attack[1];
	cout << Attack[0] << " " << Attack[1] << endl;

	*fichier >> tmp;
	cout << tmp << endl;
	*fichier >> Defense[0];
	*fichier >> Defense[1];
	cout << Defense[0] << " " << Defense[1] << endl;

	*fichier >> tmp;
	cout << tmp << endl;
	*fichier >> Paralysis;
	cout << Paralysis << endl;

	*fichier >> tmp;
	*fichier >> Wake;
	cout << tmp << endl;
	cout << Wake << endl;
	*fichier >> tmp;		// lit EndMonster

	monElec = new CElectric(Paralysis, Wake, nomMonstre, frand_a_b(HP[0], HP[1]), frand_a_b(speed[0], speed[1]), frand_a_b(Defense[0], Defense[1]), frand_a_b(Attack[0], Attack[1]));

	return monElec;
}

// fonction lecture et création de monstre propre à chaque type
CWater* lecture_Water(ifstream *fichier, string nomMonstre, CTerrain *terrain)
{
	CWater *monWater = NULL;

	unsigned int t = (unsigned int)time(NULL);		// va nous servir pour calculer des valeurs aléatoires
	srand(t);

	float HP[2];
	float speed[2];
	float Attack[2];
	float Defense[2];
	float flood;
	float fall;

	string tmp;			// va contenir les mots du fichier

	*fichier >> HP[0];
	*fichier >> HP[1];
	cout << HP[0] << " " << HP[1] << endl;

	*fichier >> tmp;
	cout << tmp << endl;
	*fichier >> speed[0];
	*fichier >> speed[1];
	cout << speed[0] << " " << speed[1] << endl;

	*fichier >> tmp;
	cout << tmp << endl;
	*fichier >> Attack[0];
	*fichier >> Attack[1];
	cout << Attack[0] << " " << Attack[1] << endl;

	*fichier >> tmp;
	cout << tmp << endl;
	*fichier >> Defense[0];
	*fichier >> Defense[1];
	cout << Defense[0] << " " << Defense[1] << endl;

	*fichier >> tmp;
	*fichier >> flood;
	cout << tmp << endl;
	cout << flood << endl;

	*fichier >> tmp;
	*fichier >> fall;
	cout << tmp << endl;
	cout << fall << endl;
	*fichier >> tmp;		// lit EndMonster

	monWater = new CWater(flood, fall, nomMonstre, frand_a_b(HP[0], HP[1]), frand_a_b(speed[0], speed[1]), frand_a_b(Defense[0], Defense[1]), frand_a_b(Attack[0], Attack[1]), terrain);

	return monWater;
}

// fonction lecture et création de monstre propre à chaque type
CFire* lecture_Fire(ifstream *fichier, string nomMonstre)
{
	CFire *monFire = NULL;

	unsigned int t = (unsigned int)time(NULL);		// va nous servir pour calculer des valeurs aléatoires
	srand(t);

	float HP[2];
	float speed[2];
	float Attack[2];
	float Defense[2];

	string tmp;			// va contenir les mots du fichier

	*fichier >> HP[0];
	*fichier >> HP[1];
	cout << HP[0] << " " << HP[1] << endl;

	*fichier >> tmp;
	cout << tmp << endl;
	*fichier >> speed[0];
	*fichier >> speed[1];
	cout << speed[0] << " " << speed[1] << endl;

	*fichier >> tmp;
	cout << tmp << endl;
	*fichier >> Attack[0];
	*fichier >> Attack[1];
	cout << Attack[0] << " " << Attack[1] << endl;

	*fichier >> tmp;
	cout << tmp << endl;
	*fichier >> Defense[0];
	*fichier >> Defense[1];
	cout << Defense[0] << " " << Defense[1] << endl;

	*fichier >> tmp;		// lit EndMonster

	monFire = new CFire(nomMonstre, frand_a_b(HP[0], HP[1]), frand_a_b(speed[0], speed[1]), frand_a_b(Defense[0], Defense[1]), frand_a_b(Attack[0], Attack[1]));

	return monFire;
}

// fonction lecture et création de monstre propre à chaque type
CInsect* lecture_Insect(ifstream *fichier, string nomMonstre)
{
	CInsect *monInsect = NULL;

	unsigned int t = (unsigned int)time(NULL);		// va nous servir pour calculer des valeurs aléatoires
	srand(t);

	float HP[2];
	float speed[2];
	float Attack[2];
	float Defense[2];

	string tmp;			// va contenir les mots du fichier

	*fichier >> HP[0];
	*fichier >> HP[1];
	cout << HP[0] << " " << HP[1] << endl;

	*fichier >> tmp;
    cout << tmp << endl;
	*fichier >> speed[0];
	*fichier >> speed[1];
    cout << speed[0] << " " << speed[1] << endl;

	*fichier >> tmp;
    cout << tmp << endl;
	*fichier >> Attack[0];
	*fichier >> Attack[1];
	cout << Attack[0] << " " << Attack[1] << endl;

	*fichier >> tmp;
	cout << tmp << endl;
	*fichier >> Defense[0];
	*fichier >> Defense[1];
	cout << Defense[0] << " " << Defense[1] << endl;

	*fichier >> tmp;		// lit EndMonster

	monInsect = new CInsect(nomMonstre, frand_a_b(HP[0], HP[1]), frand_a_b(speed[0], speed[1]), frand_a_b(Defense[0], Defense[1]), frand_a_b(Attack[0], Attack[1]));

	return monInsect;
}

// fonction lecture et création de monstre propre à chaque type
CPlant* lecture_Plant(ifstream *fichier, string nomMonstre)
{
	CPlant *monPlant = NULL;

	unsigned int t = (unsigned int)time(NULL);		// va nous servir pour calculer des valeurs aléatoires
	srand(t);

	float HP[2];
	float speed[2];
	float Attack[2];
	float Defense[2];
	float Probasoigne;

	string tmp;			// va contenir les mots du fichier

	*fichier >> HP[0];
	*fichier >> HP[1];
	cout << HP[0] << " " << HP[1] << endl;

	*fichier >> tmp;
	cout << tmp << endl;
	*fichier >> speed[0];
	*fichier >> speed[1];
	cout << speed[0] << " " << speed[1] << endl;

	*fichier >> tmp;
	cout << tmp << endl;
	*fichier >> Attack[0];
	*fichier >> Attack[1];
	cout << Attack[0] << " " << Attack[1] << endl;

	*fichier >> tmp;
	cout << tmp << endl;
	*fichier >> Defense[0];
	*fichier >> Defense[1];
	cout << Defense[0] << " " << Defense[1] << endl;

	*fichier >> tmp;
	*fichier >> Probasoigne;
	cout << tmp << endl;
	cout << Probasoigne << endl;
	*fichier >> tmp;		// lit EndMonster

	monPlant = new CPlant(nomMonstre, frand_a_b(HP[0], HP[1]), frand_a_b(speed[0], speed[1]), frand_a_b(Defense[0], Defense[1]), frand_a_b(Attack[0], Attack[1]), Probasoigne);

	return monPlant;
}

// fonction lecture et création de monstre propre à chaque type
CRock* lecture_Rock(ifstream *fichier, string nomMonstre)
{
	CRock *monRock = NULL;

	unsigned int t = (unsigned int)time(NULL);		// va nous servir pour calculer des valeurs aléatoires
	srand(t);

	float HP[2];
	float speed[2];
	float Attack[2];
	float Defense[2];

	string tmp;			// va contenir les mots du fichier

	*fichier >> HP[0];
	*fichier >> HP[1];
	cout << HP[0] << " " << HP[1] << endl;

	*fichier >> tmp;
	cout << tmp << endl;
	*fichier >> speed[0];
	*fichier >> speed[1];
	cout << speed[0] << " " << speed[1] << endl;

	*fichier >> tmp;
	cout << tmp << endl;
	*fichier >> Attack[0];
	*fichier >> Attack[1];
	cout << Attack[0] << " " << Attack[1] << endl;

	*fichier >> tmp;
	cout << tmp << endl;
	*fichier >> Defense[0];
	*fichier >> Defense[1];
	cout << Defense[0] << " " << Defense[1] << endl;

	*fichier >> tmp;		// lit EndMonster

	monRock = new CRock(nomMonstre, frand_a_b(HP[0], HP[1]), frand_a_b(speed[0], speed[1]), frand_a_b(Defense[0], Defense[1]), frand_a_b(Attack[0], Attack[1]));

	return monRock;
}

// appel le bon constructeur en fonction du type
CMonster* constructor(ifstream *fichier, string nomMonstre, string type, CTerrain *terrain)
{
	CMonster *monMonstre = NULL;

	if (type.compare("Electric") == 0)
	{
		// lit le fichier et crée un monstre CElectric
		monMonstre = lecture_Elec(fichier, nomMonstre);
		printf("\n %s ajoute avec succes !", nomMonstre.c_str());
	}

	else if (type.compare("Water") == 0)
	{
		// lit le fichier et crée un monstre CWater
		monMonstre = lecture_Water(fichier, nomMonstre, terrain);
		printf("\n %s ajoute avec succes !", nomMonstre.c_str());
	}

	else if (type.compare("Fire") == 0)
	{
		// lit le fichier et crée un monstre CFire
		monMonstre = lecture_Fire(fichier, nomMonstre);
		printf("\n %s ajoute avec succes !", nomMonstre.c_str());
	}

	else if (type.compare("Insect") == 0)
	{
		// lit le fichier et crée un monstre CInsect
		monMonstre = lecture_Insect(fichier, nomMonstre);
		printf("\n %s ajoute avec succes !", nomMonstre.c_str());
	}


	else if (type.compare("Plant") == 0)
	{
		// lit le fichier et crée un monstre CPlant
		monMonstre = lecture_Plant(fichier, nomMonstre);
		printf("\n %s ajoute avec succes !", nomMonstre.c_str());
	}

	else if (type.compare("Rock") == 0)
	{
		// lit le fichier et crée un monstre CRock
		monMonstre = lecture_Rock(fichier, nomMonstre);
		printf("\n %s ajoute avec succes !", nomMonstre.c_str());
	}

	else
		printf("\n Erreur le type %s n'existe pas !", nomMonstre.c_str());

	return monMonstre;
}

// recherche le nom du monstre dans le fichier
// s'il est présent, elle renvoie son type
string rechercheMonster(ifstream *fichier, string str_tosearch)
{
	string mot = "0";				// va stocker les mots du fichier

	// on recherche le nom du monstre dans le fichier ainsi que son type

	if (fichier)
	{
		string ligne;				// variable pour stocker les lignes lues
		bool trouve = false;		// indique si on a trouvé le nom du monstre dans le fichier
		streamoff position = 0;		// position de la chaine trouvé dans le fichier

		// on se positionne au début du fichier
		fichier->seekg(0, fichier->beg);

		while (*fichier >> ligne && trouve == false) //Tant qu'on n'est pas à la fin, on lit
		{
			cout << ligne << endl;
			//Et on l'affiche dans la console
			if (ligne.compare(str_tosearch.c_str()) == 0)
			{
				trouve = true;
				position = fichier->tellg();
				cout << " Monstre trouve ! a l'octet " << position << '\n' << endl;

				// on lit le type de monstre à créer
				*fichier >> mot;
				*fichier >> mot;
			cout << mot << endl;
			}
		}
		// si on ne trouve pas le nom du monstre
		if (trouve == false)
			printf("\n IMPOSSIBLE DE TROUVER %s !", str_tosearch.c_str());
	}
	return mot;
}


// initialise le tableau de monstre 
vector<CMonster*> InitMonster(int joueur, ifstream *fichier, CTerrain *terrain, vector<CMonster *> Tabmonstres, int cpt, int nbMonstre)
{
	string nomChoisi[3];					// va stocker les noms des monstres de l'user
	string typeMonstre;						// va stocker le type des monstres

	/* 2 */ // choix de l'user de ses monstres
	printf("\n\n===> Joueur %d, Tapez le nom du monstre pour l'ajouter a votre Team (%d/%d): ", joueur, cpt + 1, nbMonstre);
	cin >> nomChoisi[cpt];

	// on recherche le nom du monstre dans le fichier ainsi que son type
	typeMonstre = rechercheMonster(fichier, nomChoisi[cpt]);
	if (typeMonstre.compare("0") == 0)
	{
		printf("\n Monstre incorrect !!!");
		return Tabmonstres;
	}

	/* 3 */ // stockage du monstre dans le vector

	// appel de la fonction de création spécifique de monstre en fonction
	Tabmonstres.push_back(constructor(fichier, nomChoisi[cpt], typeMonstre, terrain));

	// Affichage de tous les monstres du joueur
	Tabmonstres[cpt]->printMonstre();

	return Tabmonstres;
}


// va créer la tableau de 3 monstres de chaques joueurs
vector<CMonster*> createMonstre(int joueur, string const nomFichier, string nomfichierAttack, CTerrain *terrain, int nbMonstre, int NbAttack)
{
	std::vector<CMonster *> Tabmonstres;
	int cpt = 0, i = NbAttack;
	ifstream fichier;
	ifstream fichierAttack;

	/* 1 */ // affichage fichier
	affichageFichier(nomFichier);

	// on ouvre le fichier
	fichier.open(nomFichier.c_str());

	// remplissage du tableau de monstre
	for (cpt = 0; cpt < nbMonstre; cpt++)
	{
		Tabmonstres = InitMonster(joueur, &fichier, terrain, Tabmonstres, cpt, nbMonstre);
	}

	// affectation des attacks aux monstres
	fichierAttack.open(nomfichierAttack);
	for (cpt = 0; cpt <nbMonstre; cpt++)
	{
		// remet le curseur au début du fichier
		fichierAttack.seekg(0, fichierAttack.beg);

		for (; i>0; i--)
		{
			// ajoute l'attaque au monstre
			Tabmonstres[cpt]->addAttack(AttackFill(&fichierAttack, Tabmonstres[cpt]->getTypeAttack(), Tabmonstres[cpt]->getAttackTab()));	
		}
		i = NbAttack;
		//Tabmonstres[cpt]->PrintAttack();
	}

	// on referme les fichiers
	fichierAttack.close();
	fichier.close();

	return Tabmonstres;
}



// affiche le tableau de monstre en paramètre
int AffichageMonstre(vector<CMonster *> Tabmonstres, int joueur)
{
	unsigned int i = 0;
	int cpt = 0;		// compte le nombre de monstre disponible

	printf("\n\n\n\n\n===============> Joueur %d, voici votre Team : ", joueur);

	// parcourt du tableau
	for (i = 0; i < Tabmonstres.size(); i++)
	{
		// si le monstre est en vie on peut le selectionner
		if (Tabmonstres[i]->getPoinVie()>0)
		{
			cpt++;
			Tabmonstres[i]->printMonstre();
			printf("==========> Tapez %d pour l'utiliser..	<==========\n", i);
		}
	}

	if (cpt == 0)
		printf("\n Aucune Monstre disponible !");

	return cpt;
}


// le joueur en paramètre choisit le monstre avec lequel il veut commencer
CMonster* choixMonstre(int joueur, vector<CMonster *> Tabmonstres)
{
	int choix;

	// Affichage de tous les monstres du joueurs
	AffichageMonstre(Tabmonstres, joueur);

	printf("\n Joueur %d, choisissez votre monstre pour jouer : ", joueur);
	cin >> choix;

	printf("\n %s choisit !", Tabmonstres[choix]->getName().c_str());

	return Tabmonstres[choix];
}


// démarre le jeu
//void CommencerLeJeu(vector<CMonster *> Tabmonstres1, vector<CMonster *> Tabmonstres2, CTerrain *terrain) 

void CommencerLeJeu(CPlayer *Joueur1 , CPlayer *Joueur2, CTerrain *terrain)
{
	// va stocker le monstre choisit par les joueurs pour commencer la partie
	CMonster *MonsterJ1;
	CMonster *MonsterJ2;

	// chaque joueur choisit son monstre de départ
	MonsterJ1 = choixMonstre(1, Joueur1->getMonsterTab());
	MonsterJ2 = choixMonstre(2, Joueur2->getMonsterTab());

	printf("\n\n|****************************************************|\n");
	printf("|****************************************************|\n");
	printf("|**                                                **|\n");
	printf("|**      *****  ******   ***   ******* ******      **|\n");
	printf("|**      ***      **     ***   ******    **        **|\n");
	printf("|**        ***    **    ** **  **  **    **        **|\n");
	printf("|**      *****    **    ** **  **   **   **        **|\n");
	printf("|**                                                **|\n");
	printf("|****************************************************|\n");
	printf("|****************************************************|\n");

	printf("\n\n\n|***************	UTILISATION	****************|");
	printf("\n\n\n|***************    A lire   *****************|");
	printf("\n\n|* Durant le jeu, tapez 111 pour changer de monstre... *|\n");
	printf("|* Tapez 555 pour utiliser un objet...                  *|\n");
	printf("\n|*******************************************************|\n\n");

	// choisir le monstre qui commence en fonction de sa vitesse
	if (MonsterJ1->getVitesse() > MonsterJ2->getVitesse())
		jouer(MonsterJ1, Joueur1, 1, MonsterJ2, Joueur2, terrain);
	else
		jouer(MonsterJ2, Joueur2, 2, MonsterJ1, Joueur1, terrain);

}


// pour rechercher dans le fichier d'attaque l'attaque volue 
CAttack* AttackFill(ifstream *fichier, type_a monType, vector<CAttack *> m_attack)
{
	CAttack *attack = NULL;

	if (*fichier)
	{
		string ligne;				
		bool trouve = false;		

		string name;
		float power;
		int Nbuse;
		float fail;

		while (*fichier >> ligne && trouve == false)
		{

			// conservation des noms en mémoire
			if (ligne.compare("Name") == 0)
				*fichier >> name;


			if (ligne.compare(nameTypeAttack[monType].c_str()) == 0)
			{
				trouve = true;

				cout << "Name : " << name << endl;

				// Puissance
				*fichier >> ligne;
				cout << ligne << endl;
				*fichier >> power;
				cout << power << endl;

				 //Nombre d'utilisation
				*fichier >> ligne;
				cout << ligne << endl;
				*fichier >> Nbuse;
				cout << Nbuse << endl;

				// probabilité d'échec
				*fichier >> ligne;
				cout << ligne << endl;
				*fichier >> fail;
				cout << fail << endl;

				attack = new CAttack(name, monType, Nbuse, power, fail);
			}
		}
		
		if (trouve == false)
			printf("\n IMPOSSIBLE DE TROUVER %s !", nameTypeAttack[monType].c_str());
	}

	return attack;
}


CObject* ObjectFill(ifstream *fichier, type_object monType)
{
	CObject *object = NULL;

	if (*fichier)
	{
		string ligne;				
		bool trouve = false;		

		
		if (monType == Potion)
		{
			
			string name;
			float lifeRecup = 0;
			float AttackValue = 0;

			while (*fichier >> ligne && trouve == false)
			{
				
				if (ligne.compare("Name") == 0)
					*fichier >> name;

				if (ligne.compare(nameTypeObject[monType].c_str()) == 0)
				{
					trouve = true;

					cout << "Name : " << name << endl;

					*fichier >> ligne;
					cout << ligne << endl;
					*fichier >> lifeRecup;
					cout << lifeRecup << endl;

					
					*fichier >> ligne;
					cout << ligne << endl;
					*fichier >> AttackValue;
					cout << AttackValue << endl;

					
					object = new CPotion(name, lifeRecup, AttackValue);
				}
			}

		}

		
		else if (monType == Drug)
		{
			
			string name;
			bool sechageTerrain = false;
			bool guerisionBrulure = false;

			
			while (*fichier >> ligne && trouve == false)
			{

				
				if (ligne.compare("Name") == 0)
					*fichier >> name;

				
				if (ligne.compare(nameTypeObject[monType].c_str()) == 0)
				{
					trouve = true;

					cout << "Name : " << name << endl;

					
					*fichier >> ligne;
					cout << ligne << endl;
					*fichier >> sechageTerrain;
					cout << sechageTerrain << endl;

					
					*fichier >> ligne;
					cout << ligne << endl;
					*fichier >> guerisionBrulure;
					cout << guerisionBrulure << endl;

					
					object = new CDrug(name, sechageTerrain, guerisionBrulure);
				}
			}
		}

		
		if (trouve == false)
			printf("\n IMPOSSIBLE DE TROUVER %s !", nameTypeObject[monType].c_str());
	}

	return object;
}

vector<CObject*> createTabObjet(string const nomFichier, int NbObject)
{
	std::vector<CObject *> TabObject;
	int i = 0;
	ifstream fichier;

	
	fichier.open(nomFichier.c_str());

	
	for (i = NbObject / 2; i>0; i--)
	{
		
		TabObject.push_back(ObjectFill(&fichier, Potion));
	}

	
	fichier.seekg(0, fichier.beg);

	
	for (i = NbObject / 2; i>0; i--)
	{
		
		TabObject.push_back(ObjectFill(&fichier, Drug));
	}

	
	fichier.close();

	return TabObject;
}



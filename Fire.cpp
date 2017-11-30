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
#include <iostream>
#include <fstream>
#include <string>
#include "Fire.h"
using namespace std;



// constructeur paramétrique

CFire::CFire(string nom, float point_vie, float vitesse, float defense_value, float attack_value) : CMonster(nom, point_vie, vitesse, defense_value, attack_value)
{
	m_type = Feu_Monstre;
	m_attackspe = false;
	
	
}



// l'attque qui brule l'ennemi
void CFire::bruler(CMonster *Ennemi)
{
	Ennemi->setBrule(true);
	m_attackspe = true;					// une booléenne pour faire l'attque qu'une fois 
	printf("\n Ennemi Brule !");
}

// l'activite qui serait faite par le monstre lors de son tour 
int CFire::activite(CMonster *Ennemi, CTerrain *terrain_p)
{
	//mettre à jour les états physiques du monstre avant de jouer
	m_etat = updateEtat(terrain_p);
	// mettre à jour l'etat du terrain 
	updateTerrain(terrain_p);
	// afficher l'etat du monstre  
	printStateMonster();

	// si le monstre est paralysé 
	if (m_etat.paralysie)
	{
		printf("\n Vous etes paralysie, vous ne pouvez pas jouer..");
		return 0;
	}

	// si le monstre n'a plus d'attque disponible 
	if (CMonster::PrintAttack() == 0)
	{
		// le monstre fait une attaque à main nue 
		attackMainNue(Ennemi);
	}
	// sinon le monstre choisit son attaque 
	else
	{
		unsigned int choix = 0;
		float nbAleatoire = calculeProba();

		// si le monstre peut bruler l'ennemi 
		if (m_attackspe == false)
		{
			// je choisi l'attque de mon monstre 
			printf("\n\n===> Saisissez le numero de l'attaque ou '40' pour bruler l'ennemi : ");
			// indice de l'ataque de mon monstre dans le tableau 
			cin >> choix;
			if (choix >= m_attack.size() && choix != 40 && choix != 555 && choix != 555)
			{
				printf("\n Erreur ! Tapez un numero d'attaque correct : ");
				cin >> choix;
			}

			//je brule l'ennemi 
			if (choix == 40)
			{
				bruler(Ennemi);
				return 0;
			}

			// activer le changement de monstre
			if (choix == 555)
				return choix;

			// utilisation des objets
			else if (choix == 555)
				return choix;
				
		}

		// si je ne peux pas brûler l'ennemi
		else
		{
			// le joueur choisis une attaque
			printf("\n\n===> Saisissez le numero de l'attaque : ");
			// indice de l'attaque dans le tableau d'attaque
			cin >> choix;
			if (choix >= m_attack.size() && choix != 555 && choix != 555)
			{
				printf("\n Erreur ! Tapez un numero d'attaque correct : ");
				cin >> choix;
			}

			// activer le changement de monstre
			if (choix == 555)
				return choix;

			// utiliser les objets disponibles 
			else if (choix == 555)
				return choix;
		}

		//Gérer les dégats 
		if (EnnemiFaibleType(Ennemi) == true)
		{
			// les dégâts doublés
			printf("\n Adversaire de Type faible ! ");

			// prise en compte de la proba d'échouer une attaque
			if (nbAleatoire < m_attack[choix]->getProbEchec())
				printf("\n Attaque fail !");

			// si le terrain est inondé, je peux glisser 
			else if (terrain_p->getInnonde())
			{
				glisserOuPas(choix, terrain_p, true, Ennemi);
			}


			// si le terrain est sec
			// j'applique dommage de l'attaque choisi
			else
			{
				printf("\n Degats doubles..");

				// si je suis empoisonné, je perds des dégâts = au dixième de mon attaque
				if (m_etat.empoisonne == true)
				{
					printf("\n Empoisonne, %.1f point(s) perdu(s)...", m_attack[choix]->getPuissanceAttack()*0.1f);
					applydamage(m_attack[choix]->getPuissanceAttack()*0.1f);
				}

				// si je suis brûlé je perds des dégâts en plus
				if (m_etat.brule == true)
				{
					// à chaque tour je perds un dixième de mon attaque
					printf("\n Brule, 0.1 point de votre attack perdu...");
					m_attack[choix]->setPuissanceAttack(m_attack[choix]->getPuissanceAttack()*0.90f);
				}
				Ennemi->applydamage(2 * calculdegat(Ennemi, choix));
				m_attack[choix]->MiseAJournbUtilisation();
			}
		}

		// dégâts non doublés
		else
		{
			printf("\n Adversaire de Type fort !");

			if (nbAleatoire < m_attack[choix]->getProbEchec())
				printf("\n Attaque fail !");

			// si le terrain est inondé, je peux glisser 
			else if (terrain_p->getInnonde())
			{
				glisserOuPas(choix, terrain_p, false, Ennemi);
			}

			// si le terrain est sec
			// applique dommage de l'attaque choisi
			else
			{
				printf("\n Degats non doubles..");

				// si je suis empoisonné, je perds des dégâts = au dixième de mon attaque
				if (m_etat.empoisonne == true)
				{
					printf("\n Empoisonne, %.1f point(s) perdu(s)...", m_attack[choix]->getPuissanceAttack()*0.1f);
					applydamage(m_attack[choix]->getPuissanceAttack()*0.1f);
				}

				// si je suis brûlé je perds des dégâts en plus
				if (m_etat.brule == true)
				{
					// à chaque tour je perds un dixième de mon attaque
					printf("\n Brule, 0.1 point de votre attack perdu...");
					m_attack[choix]->setPuissanceAttack(m_attack[choix]->getPuissanceAttack()*0.90f);
				}
				Ennemi->applydamage(calculdegat(Ennemi, choix));
				m_attack[choix]->MiseAJournbUtilisation();
			}
		}
	}
	return 0;
}

// afin de vérifier si l'adversaire est de type faibe ^^
bool CFire::EnnemiFaibleType(CMonster *Ennemi)
{
	// pour vérifier si l'adversaire est de type herbe ( type faible )
	if (Ennemi->getTypeMonstre() == Herbe_Monstre)
		return true;

	else
		return false;
}

CFire::~CFire()
{

}

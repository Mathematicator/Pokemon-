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
#include "Water.h"
#include "terrain.h"
#include "time.h"
using namespace std;

// constructeur paramétrique
CWater::CWater(float flood, float fall, string nom, float point_vie, float vitesse, float defense_value, float attack_value, CTerrain *terrain) : CMonster(nom, point_vie, vitesse, defense_value, attack_value)
{
	m_flood = flood;
	m_fall = fall;
	m_type = Eau_Monstre;

	// application de la probabilité de l'adversaire de chuter sur sol inondé
	terrain->setFallTerrain(fall);

	/*
	// ajout des attacks avec constructeurs des attacks
	m_attack.push_back(new CAttack("Attack Eau 1", Eau, 1, 5, 0.2f));
	m_attack.push_back(new CAttack("Attack Eau 2", Eau, 2, 7, 0.5f));
	*/
}



// activite que va faire le joueur
int CWater::activite(CMonster *Ennemi, CTerrain *terrain_p)
{
	// Mise A Jour des états physiques de mon monstre avant de jouer
	m_etat = updateEtat(terrain_p);
	// Mise A Jour du terrain
	updateTerrain(terrain_p);
	// affiche l'état de notre monstre 
	printStateMonster();

	// si je suis paralysé je ne peux pas jouer
	if (m_etat.paralysie)
	{
		printf("\n Vous etes paralysie, vous ne pouvez pas jouer..");
		return 0;
	}

	
	// si je n'ai pas d'attaque disponible
	else if (CMonster::PrintAttack() == 0)
	{
		// je combats à main nue
		attackMainNue(Ennemi);
	}
	// sinon je choisis une attaque
	else
	{
		unsigned int choix = 0;
		float nbAleatoire = calculeProba();

		// je choisis une attaque
		printf("\n\n===> Saisissez le numero de l'attaque : ");
		// indice de l'attaque dans le tableau d'attaque
		cin >> choix;
		if (choix >= m_attack.size() && choix != 555 && choix != 555)
		{
			printf("\n Erreur ! Tapez un numero d'attaque correct : ");
			cin >> choix;
		}

		// activation du changement de monstre
		if (choix == 555)
			return choix;

		// utilisation des objets
		else if (choix == 555)
			return choix;

		/* GESTION DEGATS */
		if (EnnemiFaibleType(Ennemi) == true)
		{
			// dégâts doublés
			printf("\n Adversaire de Type faible ! ");

			// prise en compte de la proba d'échouer une attaque
			if (nbAleatoire < m_attack[choix]->getProbEchec())
				printf("\n Attaque fail !");

			// applique dommage de l'attaque choisi
			else
			{
				printf("\n Degats doubles..");
				// j'essaie d'inonder le terrain s'il ne l'est pas
				if (terrain_p->getInnonde() == false)
					flood(terrain_p);

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

				// j'essaie d'inonder le terrain s'il ne l'est pas
				if (terrain_p->getInnonde() == false)
					flood(terrain_p);

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

	

// qui indiquera si le terrain est innondé ou non suite à l’attaque.
bool CWater::flood(CTerrain *terrain_p)
{
	float nbAleatoire = calculeProba();

	if (nbAleatoire < m_flood)
	{
		// inondation du terrain
		terrain_p->setInnonde(true);
		// incrémente le nombre de tour inondé du terrain
		//terrain_p->setNbtour(terrain_p->getNbTour() + 1);		
		return true;						// terrain inondé
	}

	else return false;

}

// vérifie si l'adversaire est de type faible
bool CWater::EnnemiFaibleType(CMonster *Ennemi)
{
	// on vérifie si l'adversaire est de type feu ( type faible )
	if (Ennemi->getTypeMonstre() == Feu_Monstre)
		return true;

	else
		return false;
}

// destructeur
CWater::~CWater()
{

}

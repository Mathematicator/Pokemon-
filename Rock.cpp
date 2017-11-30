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
#include "Rock.h"
#include "time.h"
#include "Monster.h"
using namespace std;



// constructeur param�trique
CRock::CRock(string nom, float point_vie, float vitesse, float defense_value, float attack_value) : CMonster(nom, point_vie, vitesse, defense_value, attack_value)
{
	m_monstre_cache = false;
	m_nbTour = 0;
	m_type = Terre_Monstre;

	/*
	// ajout des attacks avec constructeurs des attacks
	m_attack.push_back(new CAttack("Attack Terre 1", Terre, 1, 5, 0.2f));
	m_attack.push_back(new CAttack("Attack Terre 2", Terre, 2, 7, 0.15f));
	*/
}


/* Les monstres de terre (CRock) poss�dent la capacit� de se cacher sous terre durant un � trois tours.
Cela a pour effet de multiplier par deux leur d�fense et d��tre ainsi plus r�sistant aux d�g�ts de son adversaire.*/
void CRock::cacher()
{
	m_monstre_cache = true;

	// multiplication par deux de la defense
	m_defense_value *= 2;

	// incr�mentation du nombre de tour cach�
	m_nbTour++;

	printf("\n Monstre cache !! Defense x2.. Nombre(s) de tour(s) cache restant : %d sur 3", 3-m_nbTour);
}

// met � jour l'�tat cach� du monstre avant son tour
void CRock::MiseAJourCacher()
{
	// si le monstre est cach�, il sort de sa cachette
	if (m_monstre_cache == true)
	{
		// on restitue l'�tat du mnostre � celui ou il �tait quand il n'�tait pas cach�
		m_monstre_cache = false;
		m_defense_value /= 2;
	}
}

// activite que fera le monstre pendant son tour
int CRock::activite(CMonster *Ennemi, CTerrain *terrain_p)
{
	
	m_etat = updateEtat(terrain_p);
	// Mise A Jour du terrain
	updateTerrain(terrain_p);
	// affiche l'�tat de notre monstre 
	printStateMonster();
	// mise � jour de l'�tat cach� de mon monstre
	MiseAJourCacher();

	
	if (m_etat.paralysie)
	{
		printf("\n Vous etes paralysie, vous ne pouvez pas jouer..");
		return 0;
	}

	
	if (CMonster::PrintAttack() == 0)
	{
		
		attackMainNue(Ennemi);
	}
	
	else
	{
		unsigned int choix = 0;
		float nbAleatoire = calculeProba();

		
		if (m_nbTour < 3)
		{
			printf("\n\n===> Saisissez le numero de l'attaque ou '30' pour vous cacher : ");
			
			cin >> choix;
			if (choix >= m_attack.size() && choix != 30 && choix != 111 && choix != 555)
			{
				printf("\n Erreur ! Tapez un numero d'attaque correct : ");
				cin >> choix;
			}

			// si j'ai choisi de me cacher et que je peux
			if (choix == 30)
			{
				cacher();
				return 0;
			}

			// activation du changement de monstre
			if (choix == 111)
				return choix;

			// utilisation des objets
			else if (choix == 555)
				return choix;
				
		}

		// si je ne peux pas me cacher
		else
		{
			// je choisis une attaque
			printf("\n\n===> Saisissez le numero de l'attaque : ");
			// indice de l'attaque dans le tableau d'attaque
			cin >> choix;
			if (choix >= m_attack.size() && choix != 111 && choix != 555)
			{
				printf("\n Erreur ! Tapez un numero d'attaque correct : ");
				cin >> choix;
			}

			// activation du changement de monstre
			if (choix == 111)
				return choix;

			// utilisation des objets
			else if (choix == 555)
				return choix;
		}

		/* GESTION DEGATS */
		if (EnnemiFaibleType(Ennemi) == true)
		{
			// d�g�ts doubl�s
			printf("\n Adversaire de Type faible ! ");

			// prise en compte de la proba d'�chouer une attaque
			if (nbAleatoire < m_attack[choix]->getProbEchec())
				printf("\n Attaque fail !");

			// si le terrain est inond�, je peux glisser 
			else if (terrain_p->getInnonde())
			{
				glisserOuPas(choix, terrain_p, true, Ennemi);
			}

			// si le terrain est sec
			// j'applique dommage de l'attaque choisi
			else
			{
				// si j'ai choisi une attaque et j'applique les d�g�ts
				printf("\n Degats doubles..");


				// si je suis empoisonn�, je perds des d�g�ts = au dixi�me de mon attaque
				if (m_etat.empoisonne == true)
				{
					printf("\n Empoisonne, %.1f point(s) perdu(s)...", m_attack[choix]->getPuissanceAttack()*0.1f);
					applydamage(m_attack[choix]->getPuissanceAttack()*0.1f);
				}

				// si je suis br�l� je perds des d�g�ts en plus
				if (m_etat.brule == true)
				{
					// � chaque tour je perds un dixi�me de mon attaque
					printf("\n Brule, 0.1 point de votre attack perdu...");
					m_attack[choix]->setPuissanceAttack(m_attack[choix]->getPuissanceAttack()*0.90f);
				}
				Ennemi->applydamage(2 * calculdegat(Ennemi, choix));
				m_attack[choix]->MiseAJournbUtilisation();
			}
		}

		// d�g�ts non doubl�s
		else
		{
			printf("\n Adversaire de Type fort !");

			if (nbAleatoire < m_attack[choix]->getProbEchec())
				printf("\n Attaque fail !");

			// si le terrain est inond�, je peux glisser 
			else if (terrain_p->getInnonde())
			{
				glisserOuPas(choix, terrain_p, false, Ennemi);
			}

			// si le terrain est sec
			// applique dommage de l'attaque choisi
			else
			{
				printf("\n Degats non doubles..");

				// si je suis empoisonn�, je perds des d�g�ts = au dixi�me de mon attaque
				if (m_etat.empoisonne == true)
				{
					printf("\n Empoisonne, %.1f point(s) perdu(s)...", m_attack[choix]->getPuissanceAttack()*0.1f);
					applydamage(m_attack[choix]->getPuissanceAttack()*0.1f);
				}

				// si je suis br�l� je perds des d�g�ts en plus
				if (m_etat.brule == true)
				{
					// � chaque tour je perds un dixi�me de mon attaque
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

bool CRock::EnnemiFaibleType(CMonster *Ennemi)
{
	
	if (Ennemi->getTypeMonstre() == Foudre_Monstre)
		return true;

	else
		return false;
}

// getter/setters
int CRock::getNbtour()
{
	return m_nbTour;
}

void CRock::setNbtour(int nbTour_p)
{
	m_nbTour = nbTour_p;
}

CRock::~CRock()
{

}
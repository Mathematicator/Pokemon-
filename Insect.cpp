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
#include "Insect.h"
#include "time.h"
using namespace std;



// constructeur paramétrique
CInsect::CInsect(string nom, float point_vie, float vitesse, float defense_value, float attack_value):CGrass(nom, point_vie, vitesse, defense_value, attack_value)
{
	m_specialactivite = false;

	/*/
	// ajout des attacks avec constructeurs des attacks
	m_attack.push_back(new CAttack("Attack Insect 1", Herbe, 1, 5, 0.2f));
	m_attack.push_back(new CAttack("Attack Insect 2", Herbe, 2, 7, 0.15f));
	*/
}


/*
Les insectes quant à eux peuvent empoisonner leurs adversaires.
A l’image de la brulure infligée par les combattants de feu,
l’empoisonnement inflige à chaque début de tour des dégâts équivalent
à un dixième de leur attaque. De même, il disparait dans le cas d’un
combat sur un terrain trempé.
*/

// empoisonne l'ennemi
void CInsect::empoisonner(CMonster *Ennemi)
{
	Ennemi->setEmpoisone(true);

	m_specialactivite = true;					// pour qu'on ne puisse faire qu'une seule fois l'attaque spéciale
	printf("\n Ennemi Empoisonne !");
}

// activite que fera le monstre
int CInsect::activite(CMonster *Ennemi, CTerrain *terrain_p)
{
	// Mise A Jour des états physiques de mon monstre avant de jouer
	m_etat = updateEtat(terrain_p);
	// Mise A Jour du terrain
	updateTerrain(terrain_p);
	// affiche l'état de notre monstre 
	printStateMonster();


	// si le terrain est inondé, je récupère un vingtième de ma vie totale
	if (terrain_p->getInnonde() == true)
	{
		printf("\n Terrain inonde, vous gagnez 1/20ie de vie !");
		setPointVie(getPoinVie() + getPoinVie()*0.20f);
	}

	// si je suis paralysé je ne peux pas jouer
	if (m_etat.paralysie)
	{
		printf("\n Vous etes paralysie, vous ne pouvez pas jouer..");
		return 0;
	}

	// si je n'ai pas d'attaque disponible
	if (CMonster::PrintAttack() == 0)
	{
		// je combats à main nue
		attackMainNue(Ennemi);
	}
	// sinon je choisis une attaque
	else
	{
		unsigned int choix = 0;
		float nbAleatoire = calculeProba();

		// si je peux empoisonner l'ennemi
		if ( m_specialactivite == false)
		{
			// je choisis une attaque
			printf("\n\n===> Saisissez le numero de l'attaque ou '50' pour empoisonner l'ennemi : ");
			// indice de l'attaque dans le tableau d'attaque
			cin >> choix;
			if (choix >= m_attack.size() && choix != 50 && choix != 99 && choix != 555)
			{
				printf("\n Erreur ! Tapez un numero d'attaque correct : ");
				cin >> choix;
			}

			// je l'empoisonne
			if (choix == 50)
			{
				empoisonner(Ennemi);
				return 0;
			}

			// activation du changement de monstre
			if (choix == 555)
				return choix;

			// utilisation des objets
			else if (choix == 555)
				return choix;

		}

		// si je ne peux pas empoisonner l'ennemi
		else
		{
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
			else if (choix == 99)
				return choix;
		}

		/* GESTION DEGATS */
		if (EnnemiFaibleType(Ennemi) == true)
		{
			// dégâts doublés
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


CInsect::~CInsect()
{

}
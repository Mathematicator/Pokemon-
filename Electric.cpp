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
#include <vector>
#include <string>
#include <fstream>
#include "time.h"
#include "Electric.h"
using namespace std;

CElectric::CElectric()
{

}


// constructeur paramétrique
CElectric::CElectric(float paralysis, float wake, string nom, float point_vie, float vitesse, float defense_value, float attack_value):CMonster(nom, point_vie, vitesse, defense_value, attack_value)
{		
	m_paralysie = paralysis;
	m_reveil = wake;
	m_type = Foudre_Monstre;

	
}

bool CElectric::paralyze(CMonster *Ennemi)
//Pour savoir si l'ennemie a subit une paralysie pendant la dérnière attaque
{
	float nbAleatoire = calculeProba();

	if (nbAleatoire < m_paralysie)
	{
		// Mise à jour de la probabilité de sortir de la paralysie du pokemon 

		Ennemi->setProbawake(m_reveil);
		// pour incrémenter pas par pas le nombre de tour où le joueur reste paralysé 
		Ennemi->setNbTourparalysie(Ennemi->getNbTourparalysie() + 1);
		// mettre la paralysie de l'ennemie en true 
		Ennemi->setparalysie(true);
		return true;						
	}

	else return false;
}


// l'activité faite par le monstre durant son tour 
int CElectric::activite(CMonster *Ennemi, CTerrain *terrain_p)
{



	// pour gérer le cas où j'ai pas d'attaques valides restatantes 
	if (CMonster::PrintAttack() == 0)
	{
		// le monstre va combattre à main nue
		attackMainNue(Ennemi);


	// cette methode met à jour les états de mon monstre avnat de jouer 
	m_etat = updateEtat(terrain_p);
	// pour mettre à jour les états du terrain
	updateTerrain(terrain_p);
	// affin d'afficher l'etat de mon monstre 
	printStateMonster();

	// cette fonction va bloquer mon tour si je suis paralysé donc je peux pas jouer par conséquence
	if (m_etat.paralysie)
	{
		printf("\n Vous etes paralysie, vous ne pouvez pas jouer..");
		return 0;
	}

	}
	// sinon je choisis une autre attaque 
	else
	{
		bool paralysie_recup = false;
		unsigned int choix = 0;
		float nbAleatoire = calculeProba();



		if (choix >= m_attack.size() && choix != 555 && choix != 555)
		{
			printf("\n Erreur ! Tapez un numero d'attaque correct : ");
			cin >> choix;
		}

		//pour activer le changement du monstre
		if (choix == 555)
			return choix;

		// pour utiliser les objets
		else if (choix == 555)
			return choix;
		// l'affichage pour choisir une attaque
		printf("\n\n===> Saisissez le numero de l'attaque : ");
		// le choix se fait par indice de l'attaque dans le tableau des attaques 
		cin >> choix;
		

		
		if (EnnemiFaibleType(Ennemi) == true)
		{
			// pour doubler les dégats
			printf("\n Adversaire de Type faible ! ");
			
			// la fonction qui permet  de prendre en compte les dégats enregistrés 
			if (nbAleatoire < m_attack[choix]->getProbEchec())
				printf("\n Attaque fail !");

			// augmenter la probabilité de glisser si le terrain est inondé 
			else if(terrain_p->getInnonde())
			{
				glisserOuPas(choix, terrain_p, true, Ennemi);
			}

			// maintenant pour un terrain sec
			// appliquer le dommage causé par l'attaque choisie
			else
			{
				printf("\n Degats doubles..");


				// la possibilité de paralysé l'adversaire si il est pas paralysé
				if (Ennemi->getEtat().paralysie == false)
					paralysie_recup = paralyze(Ennemi);

				if (paralysie_recup == true)
					printf("\n Ennemi paralysie !");

				// quand je suis sous l'effet d'empoisonnement je perds un pourcentage de dixième de mon attaque sur les dégats
				if (m_etat.empoisonne == true)
				{
					printf("\n Empoisonne, %.1f point(s) perdu(s)...", m_attack[choix]->getPuissanceAttack()*0.1f);
					applydamage(m_attack[choix]->getPuissanceAttack()*0.1f);
				}

				// si le monstre est brulé il perds plus de dégats 
				if (m_etat.brule == true)
				{
					// chaque tour passé fait perdre l'equivalent d'un dixième de mon attaque 
					printf("\n Brule, 0.1 point de votre attack perdu...");
					m_attack[choix]->setPuissanceAttack(m_attack[choix]->getPuissanceAttack()*0.90f);
				}

				Ennemi->applydamage(2 * calculdegat(Ennemi, choix));
				m_attack[choix]->MiseAJournbUtilisation();
			}
		}

		// adversaire de type fort -> dégats non doublés 
		else
		{
			printf("\n l'Adversaire est de Type fort !");
			
			if (nbAleatoire < m_attack[choix]->getProbEchec())
				printf("\n Attaque non réussie !");

			// Faire glisser le monstre si le terrain est inondé 
			else if (terrain_p->getInnonde())
			{
				glisserOuPas(choix, terrain_p, false, Ennemi);
			}

			// dans le cas où le terrain est sec 
			// appliquer les dégats de l'attaque choisie 
			else
			{
				printf("\n les dégats sont non doubles..");
				// faire en sorte de le paralysé si ce n'est pas le cas
				if (Ennemi->getEtat().paralysie == false)
					paralysie_recup = paralyze(Ennemi);

				if (paralysie_recup == true)
					printf("\n Ennemi paralysie !");

				// si le monstre est paralysé il perd des dégats égals au dixième de son attaque
				if (m_etat.empoisonne == true)
				{
					printf("\n Empoisonne, %.1f point(s) perdu(s)...", m_attack[choix]->getPuissanceAttack()*0.1f);
					applydamage(m_attack[choix]->getPuissanceAttack()*0.1f);
				}

				// si le monstre est brulé il perd des dégats en plus 
				if (m_etat.brule == true)
				{
					// il perds un dixième de son attaque à chaque tour 
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


// vérifie si l'adversaire est de type faible
bool CElectric::EnnemiFaibleType(CMonster *Ennemi)
{
	// on vérifie si l'adversaire est de type eau ( type faible )
	if (Ennemi->getTypeMonstre() == Eau_Monstre)
		return true;

	else
		return false;
}

// destructeur
CElectric::~CElectric()
{

}





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
#include "time.h"
#include "Monster.h"
using namespace std;

// constructeur par défaut
CMonster::CMonster()
{

}
// constructeur paramétrique
CMonster::CMonster(string nom, float point_vie, float vitesse, float defense_value, float attack_value)
{
	m_nom = nom;
	m_point_vie = point_vie;
	m_vitesse = vitesse;		
	m_defense_value = defense_value;
	m_attack_value = attack_value;
	
	m_etat.brule = false;
	m_etat.empoisonne = false;
	m_etat.paralysie = false;

	m_myparalysie.m_nbTour = 0;
	m_myparalysie.m_probawake = 1;					
}

/*
Dans le cas d’une attaque à mains nues, les dégâts effectués sont les suivants :
Dégât = 4 / 3 * attaque – défenseDeLAdversaire
*/
void CMonster::attackMainNue(CMonster *Ennemi)
{
	float degats;

	degats = (4 / 3)*(float)m_attack_value - Ennemi->getDefense();

	Ennemi->applydamage(degats);
}

// calcul les dégâts que le monstre applique à son adversaire
float CMonster::calculdegat(CMonster *Ennemi, int indiceAttack)
{
	// Dégât = attaque + puissanceDAttaque – défenseDeLAdversaire
	float degat = (float)(m_attack_value + m_attack[indiceAttack]->getPuissanceAttack() - Ennemi->getDefense());

	// pour éviter que l'adversaire gagne de la vie quand on l'attaque
	if (degat < 0)
	{
		degat = 0;
		printf("\n Defense de l'adversaire superieure a votre attaque! Aucun dommage...");
	}
		
	return degat;
}


// activite que fait le monstre à son tour
int CMonster::activite(CMonster *Ennemi, CTerrain *terrain_p)
{
	return 0;
}

// fait glisser le monstre (sauf de type eau) ou non lors de son attaque
void CMonster::glisserOuPas(int choix, CTerrain *terrain, bool typefaible, CMonster *Ennemi)
{
	float nbAleatoire = calculeProba();

	// si on glisse 
	if (nbAleatoire < terrain->getFallTerrain())
	{
		printf("\n Vous avez glisse !! %.1f point(s) perdu(s)...", (float)(m_attack[choix]->getPuissanceAttack()) / 4);
		// perd un nombre de point de vie égal au quart de sa propre attaque.
		applydamage((float)(m_attack[choix]->getPuissanceAttack()) / 4);
		m_attack[choix]->MiseAJournbUtilisation();
	}

	// si on ne glisse pas
	else
	{
		// on double les dégats si ennemi est de type faible
		if (typefaible == true)
		{
			printf("\n Degats doubles..");
			Ennemi->applydamage(2 * calculdegat(Ennemi, choix));
			m_attack[choix]->MiseAJournbUtilisation();
		}

		// dégats normaux si ennemi est de type fort
		else if (typefaible == false)
		{
			printf("\n Degats non doubles..");
			Ennemi->applydamage(calculdegat(Ennemi, choix));
			m_attack[choix]->MiseAJournbUtilisation();
		}
	}
}

// met à jour les états du monstre du joueur avant qu'il ne fasse une activite
etat CMonster::updateEtat(CTerrain *terrain_p)
{
	// s'il est paralysé
	if (m_etat.paralysie == true)
		m_etat = updateparalysie();

	// s'il est brulé
	if (m_etat.brule == true)
		updateBrule(terrain_p);


	// s'il est empoissoné
	if (m_etat.empoisonne == true)
		updateEmpoisone(terrain_p);

	return m_etat;
}

// met à jour l'état brulé du monstre
void CMonster::updateBrule(CTerrain *terrain_p)
{
	// si le terrain est inondé on guérit de ses brûlures
	if (terrain_p->getInnonde() == true)
	{
		setBrule(false);
		printf("\n Terrain inonde, le monstre est guerit de ses brulures!");
	}
}

// met à jour l'état empoisoné du monstre
void CMonster::updateEmpoisone(CTerrain *terrain_p)
{
	// si le terrain est inondé le monstre n'est plus empoisonné
	if (terrain_p->getInnonde() == true)
	{
		setEmpoisone(false);
		printf("\n Terrain inonde, le monstre n'est plus empoisonne !");
	}
}

// met à jour la paralysie du monstre du joueur
etat CMonster::updateparalysie()
{
	float nbAleatoire = calculeProba();

	// s'il peut sortir de sa paralysé, il en sort
	if (nbAleatoire < m_myparalysie.m_probawake || m_myparalysie.m_nbTour >= 6)
	{
		// il sort de sa paralysie
		m_etat.paralysie = false;
		// on remet à zero mon nombre de tour paralysé
		m_myparalysie.m_nbTour = 0;
		printf("\n Sortie de votre paralysie !");
	}

	// sinon on incrémente le nombre de tour
	else 
		setNbTourparalysie(getNbTourparalysie() + 1);

	return m_etat;
}

// affiche les états du monstre
void CMonster::printStateMonster()
{
	// s'il est paralysé
	if (m_etat.paralysie == true)
		printf("\n Monstre paralysie ! Nombre de tour paralysie : %d", getNbTourparalysie());

	// s'il est brulé
	if (m_etat.brule == true)
		printf("\n Monstre brule !");

	// s'il est empoissoné
	if (m_etat.empoisonne == true)
		printf("\n Monstre Empoisonne !");
}

// met à jour l'état du terrain avant chaque activite
void CMonster::updateTerrain(CTerrain *terrain_p)
{
	// si le terrain est inondé
	if (terrain_p->getInnonde() == true)
	{
		// si le nombre de tour max est atteint on sèche le terrain
		if (terrain_p->getNbTour() >= 3)
		{
			terrain_p->setInnonde(false);
			terrain_p->setNbtour(0);
		}

		else // incrémente le nombre de tour inondé du terrain
			terrain_p->setNbtour(terrain_p->getNbTour() + 1);
	}

	terrain_p->PrintetatTerrain();
}

// indique si le monstre est toujours en vie
bool CMonster::isAlive()
{
	if (m_point_vie > 0)
		return true;

	else
		return false;
}

// applique les dégâts reçus à la vie du monstre
void CMonster::applydamage(float pdamage)
{
	m_point_vie -= pdamage;

	//Pour éviter d'avoir une vie négative
	if (m_point_vie < 0) 
	{
		m_point_vie = 0;  
	}
}

// getter/setter
void CMonster::setProbawake(float probawake)
{
	m_myparalysie.m_probawake = probawake;
}

type CMonster::getTypeMonstre()
{
	return m_type;
}

// affiche les attaques disponibles
int CMonster::PrintAttack()
{
	unsigned int i = 0;
	int cpt = 0;		// compte le nombre d'attaque disponible

	printf("\n Attaque(s) disponible(s) pour %s :\n",m_nom.c_str());

	// parcourt du tableau
	for (i = 0; i < m_attack.size(); i++)
	{
		// on vérifie si l'attaque est disponible
		if (m_attack[i]->getNbUtilisation()>0)
		{
			cpt++;
			m_attack[i]->printInfo();
			printf("==========> Tapez %d pour l'utiliser.. <==========\n", i);
		}	
	}

	if (cpt==0)
		printf("\n Aucune attaque disponible ! Vous devez combattre a main nue..");

	return cpt;
}

// ajoute l'attack en paramètre
void CMonster::addAttack(CAttack *attack)
{
	m_attack.push_back(attack);
}

// vérifie si l'adversaire est de type faible
bool CMonster::EnnemiFaibleType(CMonster *Ennemi)
{
	return false;
}

void CMonster::setEtat(etat etat_p)
{
	m_etat = etat_p;
}

etat CMonster::getEtat()
{
	return m_etat;
}

void CMonster::setparalysie(bool true_false)
{
	m_etat.paralysie = true_false;
}

void CMonster::setBrule(bool true_false)
{
	m_etat.brule = true_false;
}

void CMonster::setDefense(float value)
{
	m_defense_value = value;
}

float CMonster :: getVitesse()
{
	return m_vitesse;
}

float CMonster::getDefense()
{
	return m_defense_value;
}

void CMonster::setNbTourparalysie(int nb)
{
	m_myparalysie.m_nbTour = nb;
}

int CMonster::getNbTourparalysie()
{
	return	m_myparalysie.m_nbTour;
}

string CMonster::getName()
{
	return m_nom;
}


void CMonster::setEmpoisone(bool true_false)
{
	m_etat.empoisonne = true_false;
}


void CMonster::setPointVie(float value)
{
	m_point_vie = value;
}

float CMonster::getPoinVie()
{
	return m_point_vie;
}

// affiche les informations du monstre
void CMonster::printMonstre()
{
	printf("\n\n /**************************** %s ****************************/", m_nom.c_str());
	printf("\n Type : %s", nameType[m_type].c_str());


	if (m_etat.empoisonne)
		printf("\n Empoisonne");

	//if (m_etat.paralysie && (m_myparalysie.m_nbTour + 1) <= 6)
	if (m_etat.paralysie)
		printf("\n paralysie, nombre de tour paralysie : %d", m_myparalysie.m_nbTour);

	if (m_etat.brule)
		printf("\n Brule");

	printf("\n Vie : %.1f, Vitesse : %.1f, Defense : %.1f, AttackVal : %.1f, probawake : %.2f\n", m_point_vie, m_vitesse, m_defense_value, m_attack_value, m_myparalysie.m_probawake);
	//printf("\n /********************************************************************/\n");
}

// calcule une probabilité aléatoire
float CMonster::calculeProba()
{
	unsigned int t = (unsigned int)time(NULL);
	srand(t);

	// on tire un nombre aléatoire entre 0 et 100
	float nbAleatoire = (float)(rand() % 101);
	nbAleatoire = nbAleatoire / 111;		// transformation pourcentage en proba

	return nbAleatoire;
}

// renvoie le type d'attack que le monstre peut posséder
type_a CMonster::getTypeAttack()
{
	if (m_type == Terre_Monstre)
		return Terre;
	if (m_type == Foudre_Monstre)
		return Foudre;
	if (m_type == Eau_Monstre)
		return Eau;
	if (m_type == Feu_Monstre)
		return Feu;
	if (m_type == Herbe_Monstre)
		return Herbe;

	else return m_attack[0]->getType();
}

vector<CAttack *> CMonster::getAttackTab()
{
	return m_attack;
}


// destructeur
CMonster::~CMonster()
{
	// free le tableau d'attaque
	m_attack.clear();
}

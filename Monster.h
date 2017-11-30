/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */

#ifndef	MONSTER_H
#define MONSTER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Attack.h"
#include "terrain.h"
#include "time.h"
using namespace std;

// structure état
typedef struct etat_s
{
	bool empoisonne;
	bool paralysie;
	bool brule;
}etat;

// cette structure a pour but de gérer l'état de paralysie du monstre.
typedef struct paralysie_s
{
	float m_probawake;				// probabilité pour que le monstre peut se réveiller et sortir de sa paralysie.
	unsigned int m_nbTour;			// nombre paralysé du monstre (la paralysie ne peut donc pas durer plus de 6 tours).
}settingparalysie;

// enumération des types possibles de monstres
typedef enum type{ Terre_Monstre, Foudre_Monstre, Eau_Monstre,	Feu_Monstre, Herbe_Monstre };
const string nameType[5] = { "Rock", "Electric", "Water", "Fire", "Grass" };				// stocker les valeurs dans un tableau pour faciliter l'affichage des différents types.


class CMonster
{
protected:
	// Membre de la classe 
	string m_nom;
	float m_point_vie;
	float m_vitesse;					// c'est le paramètre qui détermine quel monstre va commencé en premier à attaquer
	float m_defense_value;				// puissance défensif du monstre
	float m_attack_value;				// puissance d'attaque du monstre
	etat m_etat;						// la variable qui donnent les différents étas que peut connaitre le monstre suite à une attaque spéciale à savoir empoisonnés, paralysés ou brulés.
	std::vector<CAttack *> m_attack;	// le tableau qui va contenir les attaques des monstres qui doit pas dépasser 4 attaques .
	type m_type;						// variable type qui renvoie le type du monstre
	settingparalysie m_myparalysie;		// les paramètres qui gèrent la paralysie

public:
	// méthode de la classe

	// activité qui sera faite par le monstre lors de son tour 
	int virtual activite(CMonster *Ennemi, CTerrain *terrain_p);
	void attackMainNue(CMonster *Ennemi);

	// permet d'actualiser l'état du monstre avant qu'il ne fasse une attaque
	etat updateEtat(CTerrain *terrain_p);

	// c'est a méthode qui actualise l'etat de paralysie du monstre
	etat updateparalysie();

	// c'est la méthode qui actualise l'etat de brulure du monstre
	void updateBrule(CTerrain *terrain_p);

	// c'est la méthode qui actualise l'etat d'empoisonnement du monstre
	void updateEmpoisone(CTerrain *terrain_p);

	// c'est la méthode qui actualise l'etat du terrain
	void updateTerrain(CTerrain *terrain_p);

	// permet de savoir si le montre est toujours en vie
	bool isAlive();	

	// appliquer les dégats recus lors d'une attaque au monstre 
	void applydamage(float pdamage);

	// permet d'afficher les attaques faites 
	int PrintAttack();

	// vérifie le type faible càd si le monstre est faible ou pas
 	virtual bool EnnemiFaibleType(CMonster *Ennemi);

	// permet d'afficher les informations reliés au monstre
	void printMonstre();

	//permet d'afficher les différents états du monstre
	void printStateMonster();

	// c'est la méthode qui permet de réaliser la glissade du monstre sauf pour le type eau
	void glisserOuPas(int choix, CTerrain *terrain, bool typefaible, CMonster *Ennemi);

	// 
	float calculeProba();

	// calcul les dégâts que le monstre applique à son adversaire
	float calculdegat(CMonster *Ennemi, int indiceAttack);

	// ajoute l'attack en paramètre
	void addAttack(CAttack *attack);

	// getter/setter
	void setProbawake(float probawake);
	void setEtat(etat etat_p);
	void setparalysie(bool true_false);
	void setNbTourparalysie(int nb);
	void setBrule(bool true_false);
	void setPointVie(float value);
	void setEmpoisone(bool true_false);
	void setDefense(float value);

	float getPoinVie();
	etat getEtat();
	type getTypeMonstre();
	float getVitesse();
	float getDefense();
	int getNbTourparalysie();
	string getName();
	type_a getTypeAttack();
	vector<CAttack *> getAttackTab();
	

	// constructeur / destructeur
	CMonster(string nom, float point_vie, float vitesse, float defense_value, float attack_value);
	CMonster();
	~CMonster();

};

#endif
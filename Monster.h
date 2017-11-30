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

// structure �tat
typedef struct etat_s
{
	bool empoisonne;
	bool paralysie;
	bool brule;
}etat;

// cette structure a pour but de g�rer l'�tat de paralysie du monstre.
typedef struct paralysie_s
{
	float m_probawake;				// probabilit� pour que le monstre peut se r�veiller et sortir de sa paralysie.
	unsigned int m_nbTour;			// nombre paralys� du monstre (la paralysie ne peut donc pas durer plus de 6 tours).
}settingparalysie;

// enum�ration des types possibles de monstres
typedef enum type{ Terre_Monstre, Foudre_Monstre, Eau_Monstre,	Feu_Monstre, Herbe_Monstre };
const string nameType[5] = { "Rock", "Electric", "Water", "Fire", "Grass" };				// stocker les valeurs dans un tableau pour faciliter l'affichage des diff�rents types.


class CMonster
{
protected:
	// Membre de la classe 
	string m_nom;
	float m_point_vie;
	float m_vitesse;					// c'est le param�tre qui d�termine quel monstre va commenc� en premier � attaquer
	float m_defense_value;				// puissance d�fensif du monstre
	float m_attack_value;				// puissance d'attaque du monstre
	etat m_etat;						// la variable qui donnent les diff�rents �tas que peut connaitre le monstre suite � une attaque sp�ciale � savoir empoisonn�s, paralys�s ou brul�s.
	std::vector<CAttack *> m_attack;	// le tableau qui va contenir les attaques des monstres qui doit pas d�passer 4 attaques .
	type m_type;						// variable type qui renvoie le type du monstre
	settingparalysie m_myparalysie;		// les param�tres qui g�rent la paralysie

public:
	// m�thode de la classe

	// activit� qui sera faite par le monstre lors de son tour 
	int virtual activite(CMonster *Ennemi, CTerrain *terrain_p);
	void attackMainNue(CMonster *Ennemi);

	// permet d'actualiser l'�tat du monstre avant qu'il ne fasse une attaque
	etat updateEtat(CTerrain *terrain_p);

	// c'est a m�thode qui actualise l'etat de paralysie du monstre
	etat updateparalysie();

	// c'est la m�thode qui actualise l'etat de brulure du monstre
	void updateBrule(CTerrain *terrain_p);

	// c'est la m�thode qui actualise l'etat d'empoisonnement du monstre
	void updateEmpoisone(CTerrain *terrain_p);

	// c'est la m�thode qui actualise l'etat du terrain
	void updateTerrain(CTerrain *terrain_p);

	// permet de savoir si le montre est toujours en vie
	bool isAlive();	

	// appliquer les d�gats recus lors d'une attaque au monstre 
	void applydamage(float pdamage);

	// permet d'afficher les attaques faites 
	int PrintAttack();

	// v�rifie le type faible c�d si le monstre est faible ou pas
 	virtual bool EnnemiFaibleType(CMonster *Ennemi);

	// permet d'afficher les informations reli�s au monstre
	void printMonstre();

	//permet d'afficher les diff�rents �tats du monstre
	void printStateMonster();

	// c'est la m�thode qui permet de r�aliser la glissade du monstre sauf pour le type eau
	void glisserOuPas(int choix, CTerrain *terrain, bool typefaible, CMonster *Ennemi);

	// 
	float calculeProba();

	// calcul les d�g�ts que le monstre applique � son adversaire
	float calculdegat(CMonster *Ennemi, int indiceAttack);

	// ajoute l'attack en param�tre
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
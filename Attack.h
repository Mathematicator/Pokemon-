/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */

#ifndef	ATTACK_H
#define ATTACK_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define nbAttack 2

using namespace std;

// enuméré les différents type d'attaque
typedef enum type_a
{
	Terre,Foudre,Eau,Feu,Herbe,Normal //  pour le type normal il est commun à tous les monstres
};

const string nameTypeAttack[6] = { "Rock", "Electric", "Water", "Fire", "Grass", "Normal" };// On stock les valeurs dans untableau afin de faciliter l'affichage des valeurs.

class CAttack
{
protected:
	// Membre de la classe 
	string m_nom;
	type_a m_type;				// ce sont les types de monstre déclarer dans enum { "Rock", "Electric", "Water", "Fire", "Grass", "Normal" }  .
	int m_nb_utilisation;		// c'est le paramètre qui montionne le nombre d'utilisation des attaques il décrémente à chaque utilisation
	float m_puissance_attaque;	// donne une idée sur la puissance d'attaque et ainsi les dégats engendrés.
	float m_prob_echec;			// il s'agirait d'une probabilité engendré aléatoirement sur l'echec de l'attaque émise.
	                            // si le monstre ratte une attaque sa faculté spéciale n'est pas prise ne considération.

public:
	// méthode de la classe


	// setter/getter
	void printInfo();
	float getPuissanceAttack();
	float getProbEchec();
	int getNbUtilisation();
	type_a getType();
	
	void setPuissanceAttack(float value);
	void MiseAJournbUtilisation();
	//void setNameAttack(string name);
	

	// constructeur / destructeur
	CAttack(string nom, type_a type, int nb_utilisation, float puissance_attaque, float prob_echec);
	CAttack();
	~CAttack();

};

#endif

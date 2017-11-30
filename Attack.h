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

// enum�r� les diff�rents type d'attaque
typedef enum type_a
{
	Terre,Foudre,Eau,Feu,Herbe,Normal //  pour le type normal il est commun � tous les monstres
};

const string nameTypeAttack[6] = { "Rock", "Electric", "Water", "Fire", "Grass", "Normal" };// On stock les valeurs dans untableau afin de faciliter l'affichage des valeurs.

class CAttack
{
protected:
	// Membre de la classe 
	string m_nom;
	type_a m_type;				// ce sont les types de monstre d�clarer dans enum { "Rock", "Electric", "Water", "Fire", "Grass", "Normal" }  .
	int m_nb_utilisation;		// c'est le param�tre qui montionne le nombre d'utilisation des attaques il d�cr�mente � chaque utilisation
	float m_puissance_attaque;	// donne une id�e sur la puissance d'attaque et ainsi les d�gats engendr�s.
	float m_prob_echec;			// il s'agirait d'une probabilit� engendr� al�atoirement sur l'echec de l'attaque �mise.
	                            // si le monstre ratte une attaque sa facult� sp�ciale n'est pas prise ne consid�ration.

public:
	// m�thode de la classe


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

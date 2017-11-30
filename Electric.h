/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */

#ifndef	ELECTRIC_H
#define ELECTRIC_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Monster.h"
#include "terrain.h"
using namespace std;



/*
Ce type de Pokemon on la facult� de paralys� l'adverse pendant un certains nombre de tour ind�termin� 
en effet le monstre paralys� doit � chaque fois v�rifier et mettre � jour son �tat afin de savoir si il est
sorti de la paralysie ou pas ce qui n�cissite des m�thodes bien adapt�es.*/

class CElectric : public CMonster
{
protected:
	// Membre de la classe 
	float m_paralysie ;			// probabilit� pour que l'adversaire soit paralysier.
	float m_reveil;				// probabilit� pour que l�adversaire �chapper de la paralysie.

public:
	// m�thode de la classe

	// cette m�thode renvoie un bool�in afin de savoir si le monstre a sorti de sa paralysie ou pas.
	bool paralyze(CMonster *Ennemi);			

	// c'est l'activit� que va faire le Monstre face � son ennemi 		
	int virtual activite(CMonster *Ennemi, CTerrain *terrain_p);

	// renvoie un bool�in pour verifier si l'adversaire est faible ou pas		
	virtual bool EnnemiFaibleType(CMonster *Ennemi);

	// constructeur / destructeur
	CElectric(float paralysis, float wake, string nom, float point_vie, float vitesse, float defense_value, float attack_value);
	CElectric();
	~CElectric();
};

#endif
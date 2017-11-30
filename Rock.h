/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */

#ifndef	ROCK_H
#define ROCK_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Monster.h"
using namespace std;

/*
poss�dent la capacit� de se cacher sous terre durant un � trois tours.
Cela a pour effet de multiplier par deux leur d�fense et d��tre ainsi 
plus r�sistant aux d�g�ts de son adversaire.*/

class CRock : public CMonster
{
protected:
	
	bool m_monstre_cache;	
	int m_nbTour;			
public:
	// m�thode de la classe
	void cacher();
	void MiseAJourCacher();

	int getNbtour();
	void setNbtour(int nbTour_p);


	// afin de v�rifier si notre adversaire est faible ou pas 
	virtual bool EnnemiFaibleType(CMonster *Ennemi);

	// l'activit� que fera le monstre pendant son tour
	int virtual activite(CMonster *Ennemi, CTerrain *terrain_p);

	// constructeur / destructeur
	CRock(string nom, float point_vie, float vitesse, float defense_value, float attack_value);
	~CRock();

};

#endif

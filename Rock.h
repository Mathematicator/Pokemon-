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
possèdent la capacité de se cacher sous terre durant un à trois tours.
Cela a pour effet de multiplier par deux leur défense et d’être ainsi 
plus résistant aux dégâts de son adversaire.*/

class CRock : public CMonster
{
protected:
	
	bool m_monstre_cache;	
	int m_nbTour;			
public:
	// méthode de la classe
	void cacher();
	void MiseAJourCacher();

	int getNbtour();
	void setNbtour(int nbTour_p);


	// afin de vérifier si notre adversaire est faible ou pas 
	virtual bool EnnemiFaibleType(CMonster *Ennemi);

	// l'activité que fera le monstre pendant son tour
	int virtual activite(CMonster *Ennemi, CTerrain *terrain_p);

	// constructeur / destructeur
	CRock(string nom, float point_vie, float vitesse, float defense_value, float attack_value);
	~CRock();

};

#endif

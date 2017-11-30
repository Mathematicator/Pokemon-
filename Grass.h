/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */

#ifndef	GRASS_H
#define GRASS_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Monster.h"

using namespace std;

/*
les monstres d’herbe regroupent les monstres plantes (CPlant) et les monstres insectes (CInsect). 
La particularité de ces combattants est qu’ils récupèrent un vingtième de leur vie total s’ils 
combattent sur un terrain inondé.
*/

class CGrass : public CMonster 
{
protected:
	// Membre de la classe 

public:
	// méthode de la classe

	// donne un booléin qui caractérise si le monstre est faible ou pas 
	virtual bool EnnemiFaibleType(CMonster *Ennemi);

	// ça indique l'activité que fera le monstre à son tour
	int virtual activite(CMonster *Ennemi, CTerrain *terrain_p);

		// la particularité du Monstre.
	void virtual specialfeature();

	// constructeur / destructeur
	CGrass(string nom, float point_vie, float vitesse, float defense_value, float attack_value);
	~CGrass();

};

#endif

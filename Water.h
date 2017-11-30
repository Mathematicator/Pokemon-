/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */

#ifndef	WATER_H
#define WATER_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Monster.h"
#include "terrain.h"
#include "utils.h"
using namespace std;

/*
a la possibilité d’inonder le terrain pendant un à trois tours.Si tel est le cas, 
lorsque l’adversaire tente une attaque, il y a une chance pour que celui - ci glisse 
sur le terrain trempé.Cela a pour conséquent d’annuler l’attaque d’une part mais aussi 
de perdre un nombre de point de vie égal au quart de sa propre attaque.*/

class CWater : public CMonster
{
protected:
	// Membre de la classe 
	float m_flood;				// désigne la probalité d'inonder le terrain 
	float m_fall;				// la probabilité pour qu'un monstre tombe lorsuqe ce dernier lance une attaque dans un terrain inondé

public:
	// méthodes de la classe
	
	// une méthode qui renvoie un booléin pour savoir si le terrain a été inondé ou pas.
	bool flood(CTerrain *terrain_p); 

	// l'activité que fera le Monster pendant son tour
	int virtual activite(CMonster *Ennemi, CTerrain *terrain_p);

	// fonction de verification si l'ennemi est faible ou pas. 
	virtual bool EnnemiFaibleType(CMonster *Ennemi);

	// constructeur / destructeur
	CWater(float flood, float fall, string nom, float point_vie, float vitesse, float defense_value, float attack_value, CTerrain *terrain);
	~CWater();

};

#endif

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
Ce type de Pokemon on la faculté de paralysé l'adverse pendant un certains nombre de tour indéterminé 
en effet le monstre paralysé doit à chaque fois vérifier et mettre à jour son état afin de savoir si il est
sorti de la paralysie ou pas ce qui nécissite des méthodes bien adaptées.*/

class CElectric : public CMonster
{
protected:
	// Membre de la classe 
	float m_paralysie ;			// probabilité pour que l'adversaire soit paralysier.
	float m_reveil;				// probabilité pour que l’adversaire échapper de la paralysie.

public:
	// méthode de la classe

	// cette méthode renvoie un booléin afin de savoir si le monstre a sorti de sa paralysie ou pas.
	bool paralyze(CMonster *Ennemi);			

	// c'est l'activité que va faire le Monstre face à son ennemi 		
	int virtual activite(CMonster *Ennemi, CTerrain *terrain_p);

	// renvoie un booléin pour verifier si l'adversaire est faible ou pas		
	virtual bool EnnemiFaibleType(CMonster *Ennemi);

	// constructeur / destructeur
	CElectric(float paralysis, float wake, string nom, float point_vie, float vitesse, float defense_value, float attack_value);
	CElectric();
	~CElectric();
};

#endif
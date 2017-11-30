/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */

#ifndef	INSECT_H
#define INSECT_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Monster.h"
#include "Grass.h"

using namespace std;

/*
Les insectes quant � eux peuvent empoisonner leurs adversaires. 
A l�image de la brulure inflig�e par les combattants de feu, 
l�empoisonnement inflige � chaque d�but de tour des d�g�ts �quivalent 
� un dixi�me de leur attaque. De m�me, il disparait dans le cas d�un 
combat sur un terrain tremp�.
*/

class CInsect : public CGrass
{
protected:
	// Membre de la classe 
	bool m_specialactivite;			// v�rifie si l'attaque sp�ciale est faite ou pas 

public:
	// m�thode de la classe

	void empoisonner(CMonster *Ennemi);
	
	// activit� faite par le monstre				
	int virtual activite(CMonster *Ennemi, CTerrain *terrain_p);

	// constructeur / destructeur
	CInsect(string nom, float point_vie, float vitesse, float defense_value, float attack_value);
	~CInsect();

};

#endif

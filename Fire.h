/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */

#ifndef	FIRE_H
#define FIRE_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Monster.h"
using namespace std;

/*
ont la possibilit� de bruler leur adversaire. Si un monstre brule, il perdra � 
chaque tour un dixi�me de son attaque. La seule possibilit� pour un 
monstre de se gu�rir de ses brulures est de se trouver dans un terrain inond�.
*/

class CFire : public CMonster
{
protected:
	// Membre de la classe 
	bool m_attackspe;				// pour savoir si l'attaque sp�ciale brul�e est d�ja faite ou pas

public:
	// m�thode de la classe
	void bruler(CMonster *Ennemi);

	// donne un bool�in qui v�rifie si le montre est faible ou pas face � l'adversaire
	virtual bool EnnemiFaibleType(CMonster *Ennemi);

	// activit� que fera le monstre dans son tour
	int virtual activite(CMonster *Ennemi, CTerrain *terrain_p);

	// constructeur / destructeur
	CFire(string nom, float point_vie, float vitesse, float defense_value, float attack_value);
	~CFire();

};

#endif

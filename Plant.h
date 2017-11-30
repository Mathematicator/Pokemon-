/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */

#ifndef	PLANT_H
#define PLANT_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Grass.h"

using namespace std;

/*
Les monstres plantes (en plus de se r�g�n�rer dans l�eau) 
ont la facult� de se soigner
En effet, durant chacune de leurs attaques, 
ils ont une chance de gu�rir leur �tat et donc de revenir � un �tat normal.
*/
class CPlant : public CGrass
{
protected:
	// Membre de la classe 
	float m_probaSoigne;    
	float m_vieDebut;		 

public:
	// m�thode de la classe

	// La m�thode qui d�crit la facult� sp�ciale du monstre 
	void virtual specialfeature();

	// constructeur / destructeur
	CPlant(string nom, float point_vie, float vitesse, float defense_value, float attack_value, float m_probaSoigne);
	~CPlant();

};

#endif

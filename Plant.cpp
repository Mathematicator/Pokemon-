/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Monster.h"
#include "time.h"
#include "Plant.h"
using namespace std;


// constructeur param�trique
CPlant::CPlant(string nom, float point_vie, float vitesse, float defense_value, float attack_value, float probaSoigne) : CGrass(nom, point_vie, vitesse, defense_value, attack_value)
{
	m_probaSoigne = probaSoigne;



	m_vieDebut = point_vie;
}

// facult� special  
/*
Les monstres plantes(en plus de se r�g�n�rer dans l�eau) ont la facult� de se soigner
En effet, durant chacune de leurs attaques, ils ont une chance de gu�rir leur �tat et 
donc de revenir � un �tat normal.
*/
void CPlant::specialfeature()
{
	float nbAleatoire = calculeProba();

	
	if (nbAleatoire < m_probaSoigne)
	{
		
		printf("\n Vie restituee !!");
		setPointVie(m_vieDebut);
	}
}

CPlant::~CPlant()
{

}
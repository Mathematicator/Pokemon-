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


// constructeur paramétrique
CPlant::CPlant(string nom, float point_vie, float vitesse, float defense_value, float attack_value, float probaSoigne) : CGrass(nom, point_vie, vitesse, defense_value, attack_value)
{
	m_probaSoigne = probaSoigne;



	m_vieDebut = point_vie;
}

// faculté special  
/*
Les monstres plantes(en plus de se régénérer dans l’eau) ont la faculté de se soigner
En effet, durant chacune de leurs attaques, ils ont une chance de guérir leur état et 
donc de revenir à un état normal.
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
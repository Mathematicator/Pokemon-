/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */

#ifndef	POTION_H
#define POTION_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Monster.h"
#include "Object.h"


/*
	Les objets affectant une donnée (CPotion) (régénération de point de vie, augmentation de l’attaque, ..)
*/


class CPotion : public CObject
{
protected:
	// Membre de la classe 
	float m_lifeRecup;						
	float m_attackValue;					
public:
	// méthodes de la classe
	void PotionLifeRecupe(CMonster *Monster);
	void PotionAttackValue(CMonster *Monster);
	void virtual useObject(CTerrain *terrain, CMonster *monster);
	void virtual printObject();

	type_object virtual getType();
	
	CPotion(string name, float lifeRecup, float attackValue);
	~CPotion();

};

#endif
/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */


#ifndef	DRUG_H
#define DRUG_H

#include "Object.h"
#include "terrain.h"
#include "Monster.h"


/*
	Cette Classe présente les objets de CDrug à savoir (guérison de brulure, séchage du terrain, …) 
*/


class CDrug : public CObject
{
protected:
	// Membre de la classe 
	bool m_sechageTerrain;				// c'est une variable booléenne qui prend 2 valeurs si c'est true = sèche le terrain, si c'est false = le terrain reste dans son état précédent.
	bool m_guerisonBrulure;				// il s'agit aussi d'une variable booléenne qui prend 2 valeurs à savoir true = guérit la brûlure du monstre ou false = laisse le monstre dans son état précedent.

public:
	// méthodes de la classe
	
	void DrugSechageTerrain(CTerrain *terrain);
	void DrugGuerisonBrulure(CMonster *monster);
	void virtual useObject(CTerrain *terrain, CMonster *monster);
	void virtual printObject();

	type_object virtual getType();

	// Constructeurs_Destructeurs
	CDrug(string name, bool sechageTerrain, bool guerisonBrulure);
	~CDrug();

};

#endif
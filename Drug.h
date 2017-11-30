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
	Cette Classe pr�sente les objets de CDrug � savoir (gu�rison de brulure, s�chage du terrain, �) 
*/


class CDrug : public CObject
{
protected:
	// Membre de la classe 
	bool m_sechageTerrain;				// c'est une variable bool�enne qui prend 2 valeurs si c'est true = s�che le terrain, si c'est false = le terrain reste dans son �tat pr�c�dent.
	bool m_guerisonBrulure;				// il s'agit aussi d'une variable bool�enne qui prend 2 valeurs � savoir true = gu�rit la br�lure du monstre ou false = laisse le monstre dans son �tat pr�cedent.

public:
	// m�thodes de la classe
	
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
/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */

#ifndef	PLAYER_H
#define PLAYER_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Monster.h"
#include "Object.h"
using namespace std;


class CPlayer 
{
protected:
	// Membre de la classe 
	vector<CMonster *> m_Tabmonstres;		// un tableau de monstres  
	vector<CObject *> m_TabObjects;		// un  tableau d'objets qui doit pas dépasser 5

public:
	// méthodes de la classe
	void addObject(CObject *Object);  // Pour ajouter des objets 
	int printObject();                 // afin d'afficher les objets ajoutés 
	void useObject(int num, CTerrain *terrain, CMonster *monster);   // utiliser ces objets 

	// getter/seters
	void setMonsterTab(vector<CMonster *> Tab);
	void setObjectTab(vector<CObject*> Tab);
	vector<CMonster *> getMonsterTab();
	vector<CObject *> getObjectTab();

	CPlayer();
	~CPlayer();

};

#endif

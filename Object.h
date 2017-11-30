/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */

#ifndef	OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "terrain.h"
#include "Monster.h"
using namespace std;

#define nbObjet 2


// enumération des différents types d'objet possibles
typedef enum type_object{ Potion, Drug };

// afin de faciliter l'affichage on utilise un tableau 
const string nameTypeObject[2] = { "Potion", "Drug" };				


class CObject
{
protected:
	// Membre de la classe 
	string m_name;				// Le nom de notre l'objet
	type_object m_type;			// Le type de l'objet
	bool m_used;				// pour paramétere le fait qu'on peut utiliser un objet qu'une seule fois

public:
	// méthodes de la classe
	bool getUsed();                  // méthode qui determine si l'objet est utiliser ou pas 
	void virtual printObject();    // affiche l'objet appelé 
	void virtual useObject(CTerrain *terrain, CMonster *monster);  // la méthode qui permet d'utiliser notre objet 
 
	type_object virtual getType();  // la méthode qui donne le type de notre objet 


	CObject(string name);
	CObject();
	~CObject();
};

#endif
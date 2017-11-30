/*
 *       _   _  _  _  _    ___  _  _  _____ _   _  _  _  _ 
 *      | \_/ |/ \| \| |  | o \/ \| |// __|| \_/ |/ \| \| |
 *      | \_/ ( o ) \\ |  |  _( o )  (| _| | \_/ ( o ) \\ |
 *      |_| |_|\_/|_|\_|  |_|  \_/|_|\\___||_| |_|\_/|_|\_|
 *      
                  Par: Lebbat badreddine
 */

#ifndef	TERRAIN_H
#define TERRAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


class CTerrain
{
protected:
	// Membre de la classe 
	bool m_innonde;					// �a reflete l'etat du terrain si il est inond� c�d que c'est �gal � vrai=true
	unsigned int m_nbTour;			// refl�te le nombre de tour jou� avec un terrian inond� 
	float m_fall_terrain;			// probabilit� que le monstre tombe si il est sur un terrain inond� lors d'une attaque � l'exception  bien sur des monstres d'eau

public:
	// m�thodes de la classe

	// getter/setters
	void setNbtour(unsigned int nbTour);
	void setInnonde(bool monbool);
	void setFallTerrain(float prob);
	float getFallTerrain();
	bool getInnonde();
	unsigned int getNbTour();
	void PrintetatTerrain();

	// constructeur / destructeur
	CTerrain();
	~CTerrain();
};

#endif
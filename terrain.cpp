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
#include <vector>
#include <string>
#include "terrain.h"
using namespace std;

// constructeur par defaut
CTerrain::CTerrain()
{
	m_innonde = false,
	m_nbTour = 0;
	m_fall_terrain = false;
}

// affiche l'état du terrain
void CTerrain::PrintetatTerrain()
{
	printf("\n **** Mise A Jour du terrain ****:");
	if (m_innonde == true)
		printf("\n Etat terrain innonde, nbTour : %d\n ***********************\n", m_nbTour);
	else
		printf("\n Etat terrain sec, nbTour : %d\n ***********************\n", m_nbTour);
}

// getter/setter
void CTerrain::setInnonde(bool monbool)
{
	m_innonde = monbool;
}

void CTerrain::setNbtour(unsigned int nbTour)
{
	m_nbTour = nbTour;
}

void CTerrain::setFallTerrain(float prob)
{
	m_fall_terrain = prob;
}

float CTerrain::getFallTerrain()
{
	return m_fall_terrain;
}

bool CTerrain::getInnonde()
{
	return m_innonde;
}

unsigned int CTerrain::getNbTour()
{
	return m_nbTour;
}

// destructeur 
CTerrain::~CTerrain()
{
	
}


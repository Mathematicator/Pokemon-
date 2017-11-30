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
#include "Attack.h"
using namespace std;


CAttack::CAttack()
{

}

// constructeur paramétrique
CAttack::CAttack(string nom, type_a type, int nb_utilisation, float puissance_attaque, float prob_echec)
{
	m_nom = nom;
	m_type = type;
	m_nb_utilisation = nb_utilisation;
	m_puissance_attaque = puissance_attaque;
	m_prob_echec = prob_echec;
}

// destructeur
CAttack::~CAttack()
{

}

float CAttack::getPuissanceAttack()
{
	return m_puissance_attaque;
}

float CAttack::getProbEchec()
{
	return m_prob_echec;
}

int CAttack::getNbUtilisation()
{
	return m_nb_utilisation;
}

void CAttack::setPuissanceAttack(float value)
{
	m_puissance_attaque = value;
}

// la méthode pour décrémenter le nombre d'utilisation 
void CAttack::MiseAJournbUtilisation()
{
	m_nb_utilisation --;

	// Pour ne pas avoir une valeur négative lors de la décrémentation 
	if (m_nb_utilisation < 0)
		m_nb_utilisation = 0;
}

// méthode qui a pour role d'afficher les informations concernant l'attaque
void CAttack::printInfo()
{
	printf("\n Nom : %s", m_nom.c_str());
	printf("\n Type : %s", nameTypeAttack[m_type].c_str());
	printf("\n nb_utilisation : %d", m_nb_utilisation);
	printf("\n puissance attaque : %.1f", m_puissance_attaque);
	printf("\n Prob echec : %.2f\n", m_prob_echec);
}

type_a CAttack::getType()
{
	return m_type;
}

